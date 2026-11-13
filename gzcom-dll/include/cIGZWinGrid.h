/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * cIGZWinGrid.h
 *
 * Copyright (C) 2026 Nicholas Hayes
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, under
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <https://www.gnu.org/licenses/>.
 */

#pragma once
#include "cIGZUnknown.h"

class cIGZBuffer;
class cIGZDrawContext;
class cIGZFont;
class cIGZMessageTarget;
class cIGZString;
class cIGZWin;
class cRZRect;

static const uint32_t GZCLSID_cGZWinGrid = 0xdaa6b9bf;
static const uint32_t GZIID_cIGZWinGrid = 0xdaa6b9be;

class cIGZWinGrid : public cIGZUnknown
{
public:
	struct tGridWinProcMessageTypes
	{
		// All values have data1 = grid pointer.

		enum eGridWinProcMessageTypes : uint32_t
		{
			// data2 = CellCoordinates pointer.
			MouseDown = 0x9a1552d2,
			// data2 = CursorHitTestResultData pointer.
			MouseUp = 0x9a1552d3,
			// data2 = CursorHitTestResultData pointer.
			MouseDoubleClick = 0x9a1552d4,
			// data2 = Windows virtual key code.
			KeyDown = 0x9a1552d5,
			// data2 = CellCoordinates pointer.
			MouseMove = 0x9a1552d6,
			DropDownExit = 0x9a1552d7,
		};
	};

	struct tGridFlag
	{
		enum eGridFlag : int32_t
		{
			None = 0x0,
			CellEdit = 0x1,
			HScroll = 0x2,
			VScroll = 0x4,
			ColHeading = 0x8,
			RowHeading = 0x10,
			ColGrid = 0x20,
			RowGrid = 0x40,
			InsertMode = 0x80,
			OpaqueBackground = 0x100,
			DOutline = 0x200,
			DGridOutline = 0x400,
			CellWrap = 0x800,
			AllOwnSel = 0x1000,
			FixColCount = 0x2000,
			FixRowCount = 0x4000,
			DPastLastCol = 0x8000,
			DPastLastRow = 0x10000,
			CellOverlap = 0x20000,
			DropDownMenu = 0x40000,
			HighlightCellData = 0x80000,
		};
	};	

	enum class SelectionRules : int32_t
	{
		WholeColumn = 0,
		WholeRow = 1,
		Cell = 2
	};

	struct CellCoordinates
	{
		int32_t column;
		int32_t row;
	};

	struct CellFormat
	{
		cIGZFont* font;
		uint32_t cellColors[6];
		uint8_t wrapping;
		uint8_t columnAlignment;
		uint8_t rowAlignment;
		uint8_t borderWidth;
		uint32_t borderColor;
	};

	static_assert(sizeof(CellFormat) == 0x24);

	struct CellFormatExtra
	{
		CellFormat format;
		uint16_t widthOrHeight;
		uint16_t cachedWidthOrHeight;
	};

	static_assert(sizeof(CellFormatExtra) == 0x28);

	struct CellData
	{
		enum class Type : int32_t
		{
			None = 0,
			Window = 1,
			String = 2,
			Bitmap = 4
		};

		union tagData
		{
			cIGZWin* win;
			cIGZString* string;
			cIGZBuffer* bitmap;
		};

		Type dataType;
		int32_t column;
		int32_t row;
		tagData data;
		CellFormat* cellFormat;
		void* extraData;
		uint32_t windowFlags;
	};

	static_assert(sizeof(CellData) == 0x1c);

	struct CursorHitTestResult
	{
		enum class Type : int32_t
		{
			None = 0,
			Outside = 1,
			RowHeader = 2,
			ColumnHeader = 3,
			Corner = 4,
			Cell = 5
		};

		Type result;
	};

	struct CursorHitTestResultData
	{
		CursorHitTestResult::Type result;
		int32_t column;
		int32_t row;
	};

	struct OwnerDrawInfo
	{
		cIGZWinGrid* grid;
		int32_t column;
		int32_t row;
		cRZRect* unknown1;
		cRZRect* unknown2;
		cRZRect* unknown3;
		cIGZBuffer* activeDrawBuffer;
		cIGZDrawContext* drawContext;
		CellFormat* cellFormat;
		CellData* cellData;
		bool cellSelected;
		bool gridEnabled;
	};

	static_assert(sizeof(OwnerDrawInfo) == 0x2c);

	enum class SortOrder : int32_t
	{
		Ascending = 0,
		Decending = 1
	};
	
	typedef int32_t(*SortCallback)(CellData const* lhs, CellData const* rhs);

	virtual bool Init() = 0;
	virtual bool Shutdown() = 0;

	virtual cIGZWin* AsIGZWin() = 0;
	virtual bool Refresh() = 0;
	virtual void SetArea(int32_t left, int32_t top, int32_t right, int32_t bottom) = 0;
	virtual bool GetGridArea(cRZRect& rect) = 0;
	virtual bool GetCellArea(cRZRect& rect) = 0;

	virtual void SetFlag(tGridFlag::eGridFlag flag) = 0;
	virtual void SetFlags(tGridFlag::eGridFlag flags) = 0;
	virtual void ClearFlag(tGridFlag::eGridFlag flag) = 0;
	virtual bool IsFlagSet(tGridFlag::eGridFlag flag) = 0;
	virtual tGridFlag::eGridFlag GetFlags() = 0;

	virtual void SetDefaultFont(cIGZFont* pFont) = 0;
	virtual cIGZFont* GetDefaultFont() = 0;
	virtual bool SetDefaultFontColor(uint32_t color, int32_t index) = 0;
	virtual bool GetDefaultFontColor(uint32_t& color, int32_t index) = 0;
	virtual bool SetDefaultFontColorByColumns(uint32_t color, int32_t index, int32_t startColumn, int32_t columnCount) = 0;
	virtual bool SetDefaultFontColorByRows(uint32_t color, int32_t index, int32_t row, int32_t rowCount) = 0;
	virtual bool SetDefaultTextWrapping(bool enable) = 0;
	virtual bool GetDefaultTextWrapping() = 0;
	virtual bool GetGutters(int32_t& left, int32_t& top, int32_t& right, int32_t& bottom) = 0;
	virtual bool SetGutters(int32_t left, int32_t top, int32_t right, int32_t bottom) = 0;
	virtual bool GetCellGutters(int32_t& left, int32_t& top, int32_t& right, int32_t& bottom) = 0;
	virtual bool SetCellGutters(int32_t left, int32_t top, int32_t right, int32_t bottom) = 0;
	virtual void SetOutlineUse(bool enabled, uint32_t color) = 0;
	virtual uint32_t GetOutlineColor() = 0;

	virtual void PauseRecalculations(bool pause) = 0;
	virtual bool ActLikeAListbox(int32_t columnCellLimit, int32_t selectedItemLimit, bool allOwnSelection) = 0;
	virtual bool ScrollCellsVertically(int32_t count) = 0;
	virtual bool ScrollCellsHorizontally(int32_t count) = 0;
	virtual bool ScrollPagesVertically(int32_t count) = 0;
	virtual bool ScrollPagesHorizontally(int32_t count) = 0;
	virtual bool ScrollToColumn(int32_t column) = 0;
	virtual bool ScrollToRow(int32_t row) = 0;
	virtual bool ScrollToCell(int32_t column, int32_t row) = 0;

	virtual bool GetSelectionRules(SelectionRules& rules, int32_t& itemLimit) = 0;
	virtual bool SetSelectionRules(SelectionRules rules, int32_t itemLimit) = 0;
	virtual uint32_t GetSelectionCount() = 0;

	// GetSelections has been renamed from GetSelection to remove ambiguity with overloaded
	// function order on Windows.
	// MSVC puts every virtual overload of a name at the vtable slot of the first one declared,
	// in REVERSE declaration order.
		
	virtual bool GetSelections(CellCoordinates* rgCellCoordinates, int32_t& count) = 0;
	virtual bool GetSelection(int32_t& column, int32_t& row) = 0;
	virtual bool SetSelection(int32_t column, int32_t row) = 0;
	virtual bool AddCellToSelection(int32_t column, int32_t row, bool select) = 0;
	virtual bool GetCellIsSelected(int32_t column, int32_t row) = 0;
	virtual bool ClearSelection() = 0;

	virtual bool EnableFixedRanges(bool columns, bool rows) = 0;
	virtual bool SetCellLimits(int32_t columnCellLimit, int32_t rowCellLimit) = 0;
	virtual bool GetCellLimits(int32_t& columnLimit, int32_t& rowLimit) = 0;
	virtual bool GetCellUsedRange(cRZRect& range) = 0;
	virtual bool GetCellVisibleRange(cRZRect& range) = 0;
	virtual bool IsColumnWithinBounds(int32_t column) = 0;
	virtual bool IsRowWithinBounds(int32_t row) = 0;
	virtual bool IsCellWithinBounds(int32_t column, int32_t row) = 0;
	virtual bool GetMostRecentlyAddedCell(int32_t& column, int32_t& row) = 0;
	virtual bool SetBackgroundColor(uint32_t color) = 0;
	virtual bool SetBackgroundBitmap(cIGZBuffer* unknown1) = 0;
	virtual bool SetGridColors(int32_t columnColor, int32_t rowColor) = 0;
	virtual void GetGridColors(int32_t& columnColor, int32_t& rowColor) = 0;
	virtual bool SetDefaultTextAlignment(int32_t alignment) = 0;
	virtual bool SetDefaultTextAlignmentByColumns(int32_t columnStartIndex, int32_t count, int32_t alignment) = 0;
	virtual bool SetDefaultTextAlignmentByRows(int32_t rowStartIndex, int32_t count, int32_t alignment) = 0;
	virtual int32_t GetDefaultTextAlignment() = 0;
	virtual void SetDefaultColumnWidth(int32_t value) = 0;
	virtual bool SetColumnWidth(int32_t columnStartIndex, int32_t count, int32_t width) = 0;
	virtual void SetDefaultRowHeight(int32_t value) = 0;
	virtual bool SetRowHeight(int32_t rowStartIndex, int32_t count, int32_t height) = 0;
	virtual int32_t GetDefaultColumnWidth() = 0;
	virtual int32_t GetDefaultRowHeight() = 0;
	virtual int32_t GetColumnWidth(int32_t columnStartIndex, int32_t columnCount) = 0;
	virtual int32_t GetRowHeight(int32_t rowStartIndex, int32_t rowCount) = 0;

	virtual bool GetColumnHeaderArea(int32_t column, cRZRect& area) = 0;
	virtual bool GetRowHeaderArea(int32_t row, cRZRect& area) = 0;
	virtual void EnableHeaders(bool columnHeaders, bool rowHeaders) = 0;
	virtual bool GetHeaderSizes(int32_t& columnHeaderSize, int32_t& rowHeaderSize) = 0;
	virtual bool SetHeaderSizes(int32_t columnHeaderSize, int32_t rowHeaderSize) = 0;
	virtual bool SetHeadingFormat(CellFormat const& format) = 0;
	virtual bool GetColumnHeading(int32_t column, cIGZString& text) = 0;
	virtual bool SetColumnHeading(int32_t column, cIGZString const& text) = 0;
	virtual bool GetRowHeading(int32_t row, cIGZString& text) = 0;
	virtual bool SetRowHeading(int32_t row, cIGZString const& text) = 0;
	virtual bool ClearAllRowHeadings() = 0;
	virtual bool ClearAllColumnHeadings() = 0;

	virtual bool GetCellFormat(int32_t column, int32_t row, CellFormat& format) = 0;
	virtual bool SetCellFormat(int32_t column, int32_t row, CellFormat const& format) = 0;
	virtual bool ClearCellFormat(int32_t column, int32_t row) = 0;
	virtual bool GetColCellFormatExtra(int32_t column, CellFormatExtra** ppFormatExtra) = 0;
	virtual bool GetRowCellFormatExtra(int32_t row, CellFormatExtra** ppFormatExtra) = 0;
	virtual bool GetColRowCellFormatExtra(int32_t column, int32_t row, CellFormatExtra** ppFormatExtra) = 0;
	virtual bool SetCellFont(int32_t column, int32_t row, cIGZFont* pFont) = 0;
	virtual bool SetCellColors(int32_t column, int32_t row, int32_t index, uint32_t color) = 0;
	virtual bool SetCellWrapping(int32_t column, int32_t row, int32_t wrapping) = 0;
	virtual bool SetCellAlignment(int32_t column, int32_t row, int32_t unknown3, int32_t unknown4) = 0;
	virtual bool SetCellBorder(int32_t column, int32_t row, int32_t unknown3, int32_t unknown4) = 0;
	virtual bool GetCellType(int32_t column, int32_t row, CellData::Type& type) = 0;
	virtual bool ClearCell(int32_t column, int32_t row) = 0;
	virtual bool ClearCellRect(int32_t left, int32_t top, int32_t right, int32_t bottom) = 0;
	virtual bool ClearAllCells() = 0;
	virtual bool DeleteCell(int32_t unknown1, int32_t unknown2, int32_t unknown3, int32_t unknown4) = 0;
	virtual bool DeleteColumns(int32_t startIndex, int32_t count, int32_t unknown3) = 0;
	virtual bool DeleteRows(int32_t column, int32_t row, int32_t unknown3) = 0;
	virtual bool CopyColumns(int32_t sourceIndex, int32_t destIndex, int32_t count, bool move) = 0;
	virtual bool CopyRows(int32_t sourceIndex, int32_t destIndex, int32_t count, bool move) = 0;

	virtual bool IsCellVisible(int32_t column, int32_t row) = 0;
	virtual bool MakeCellVisible(int32_t column, int32_t row) = 0;
	virtual bool GetCellRect(int32_t column, int32_t row, cRZRect& area) = 0;
	virtual bool GetFirstVisibleCell(int32_t& column, int32_t& row) = 0;
	virtual bool SetFirstVisibleCell(int32_t column, int32_t row) = 0;
	virtual bool GetVisibleColumnAndRowCount(float& columnCount, float& rowCount) = 0;
	virtual bool DoCursorHitTest(int32_t cursorX, int32_t cursorY, CursorHitTestResult& result, CellCoordinates& coords) = 0;
	virtual bool GetCellTextValue(int32_t column, int32_t row, cIGZString& text) = 0;
	virtual bool SetCellTextValue(int32_t column, int32_t row, char const* text, uint32_t length, int32_t unknown5, bool editable) = 0;
	virtual bool GetCellBitmap(int32_t column, int32_t row, cIGZBuffer** ppBuffer) = 0;
	virtual bool SetCellBitmap(int32_t column, int32_t row, cIGZBuffer* pBuffer, int32_t unknown4) = 0;
	virtual bool GetCellWindow(int32_t column, int32_t row, cIGZWin** ppWindow) = 0;
	virtual bool SetCellWindow(int32_t column, int32_t row, cIGZWin* pWin, bool dynamicWidth, bool dynamicHeight, int32_t unknown6) = 0;
	virtual bool IsWindowACellWindow(cIGZWin* pWin, uint32_t windowID, int32_t* column, int32_t* row) = 0;
	virtual void ResizeColumnToFitCellWindows(int32_t column, int32_t row) = 0;

	virtual bool SetCellExtraData(int32_t column, int32_t row, void* data) = 0;
	virtual void* GetCellExtraData(int32_t column, int32_t row) = 0;
	virtual bool SetColumnExtraData(int32_t column, void* data) = 0;
	virtual void* GetColumnExtraData(int32_t column) = 0;
	virtual bool SetRowExtraData(int32_t row, void* data) = 0;
	virtual void* GetRowExtraData(int32_t row) = 0;
	virtual bool SetExtraData(void* data) = 0;
	virtual void* GetExtraData() = 0;
	virtual bool GetCellExtraDataObject(int32_t column, int32_t row, uint32_t riid, void** ppvObj) = 0;
	virtual bool SetCellExtraDataObject(int32_t column, int32_t row, cIGZUnknown* pUnknown) = 0;
	virtual bool GetExtraDataObject(uint32_t riid, void** ppvObj) = 0;
	virtual bool SetExtraDataObject(cIGZUnknown* pUnknown) = 0;

	virtual void SortColumn(int32_t columnStartIndex, SortOrder sortOrder, bool sortAll, SortCallback callback) = 0;
	virtual void SortRow(int32_t rowStartIndex, SortOrder sortOrder, bool sortAll, SortCallback callback) = 0;
	virtual bool FindCellText(char const* text, uint32_t textLength, int32_t unknown3, int32_t unknown4, int32_t unknown5, int32_t unknown6, int32_t& outColumn, int32_t& outRow, bool exact) = 0;
	virtual bool SetOwnerDrawNotification(cIGZMessageTarget* pMessageTarget) = 0;
	virtual bool GetBufferToDrawTo(cIGZBuffer** ppBuffer, cRZRect& drawArea) = 0;
	virtual bool SetScrollBarImageVertical(cIGZBuffer* buffer, cRZRect const& area) = 0;
	virtual bool SetScrollBarImageHorizontal(cIGZBuffer* buffer, cRZRect const& area) = 0;
	virtual bool SetSoundID(int32_t index, int32_t id) = 0; // Index must be in the range of 0-2.
	virtual bool MakeDropDown() = 0;
};
