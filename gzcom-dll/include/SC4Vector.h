/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * SC4Vector.h
 *
 * Copyright (C) 2025, 2026 Nicholas Hayes
 * Copyright (C) 2025 memo
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
#include "cIGZAllocatorService.h"
#include "GZServPtrs.h"
#include <cstdint>
#include <memory>
#include <stdexcept>

template<typename T> class SC4Vector
{
public:
	using value_type = T;
	using pointer = value_type*;
	using const_pointer = const pointer;
	using reference = value_type&;
	using const_reference = const value_type&;
	using iterator = pointer;
	using const_iterator = const_pointer;

	SC4Vector()
		: mpStart(nullptr), mpEnd(nullptr), mpCapacity(nullptr)
	{
	}

	SC4Vector(const SC4Vector<T>& other)
		: mpStart(nullptr), mpEnd(nullptr), mpCapacity(nullptr)
	{
		operator=(other);
	}

	SC4Vector(SC4Vector<T>&& other)
		: mpStart(nullptr), mpEnd(nullptr), mpCapacity(nullptr)
	{
		operator=(other);
	}

	~SC4Vector()
	{
		if (mpStart != nullptr)
		{
			destroy_contents(mpStart, size());
			deallocate(mpStart);

			mpStart = nullptr;
			mpEnd = nullptr;
			mpCapacity = nullptr;
		}
	}

	SC4Vector<T>& operator=(const SC4Vector<T>& other)
	{
		if (&other != this)
		{
			clear();

			size_t newSize = other.size();

			if (newSize > 0)
			{
				push_back(other.mpStart, newSize);

				if constexpr (std::is_base_of_v<cIGZUnknown, std::remove_pointer_t<T>>)
				{
					for (size_t i = 0; i < newSize; i++)
					{
						if constexpr (std::is_pointer_v<T>)
						{
							other.mpStart[i]->AddRef();
						}
						else
						{
							other.mpStart[i].AddRef();
						}
					}
				}
			}
		}

		return *this;
	}

	SC4Vector<T>& operator=(SC4Vector<T>&& other)
	{
		if (&other != this)
		{
			mpStart = std::exchange(other.mpStart, nullptr);
			mpEnd = std::exchange(other.mpEnd, nullptr);
			mpCapacity = std::exchange(other.mpCapacity, nullptr);
		}

		return *this;
	}

	iterator begin()
	{
		return mpStart;
	}

	iterator end()
	{
		return mpEnd;
	}

	const_iterator begin() const
	{
		return mpStart;
	}

	const_iterator end() const
	{
		return mpEnd;
	}

	const_iterator cbegin() const
	{
		return mpStart;
	}

	const_iterator cend() const
	{
		return mpEnd;
	}

	size_t capacity() const
	{
		return mpCapacity - mpStart;
	}

	void clear()
	{
		destroy_contents(mpStart, size());
		mpEnd = mpStart;
	}

	pointer data() const
	{
		return mpStart;
	}

	bool empty() const
	{
		return mpStart == mpEnd;
	}

	iterator erase(iterator position)
	{
		if ((position + 1) != end())
		{
			std::move(position + 1, mpEnd, position);
		}

		--mpEnd;
		destroy(*mpEnd);

		return position;
	}

	void push_back(const T& value)
	{
		push_back(std::addressof(value));
	}

	void push_back(const T* value)
	{
		push_back(value, 1);
	}

	void push_back(const T* const values, size_t count)
	{
		if (count == 0)
		{
			return;
		}

		const size_t remainingCapacity = remaining_capacity();

		if (count > remainingCapacity)
		{
			reserve(capacity() + count);
		}

		memmove(mpEnd, values, count * sizeof(T));
		mpEnd = mpEnd + count;
	}

	void reserve(size_t newCapacity)
	{
		if (newCapacity > capacity())
		{
			T* newStart = allocate(newCapacity);
			T* newEnd = newStart;

			if (!empty())
			{
				const size_t existingSize = size();

				memmove(newStart, mpStart, existingSize * sizeof(T));
				deallocate(mpStart);
				newEnd = newStart + existingSize;
			}

			mpStart = newStart;
			mpEnd = newEnd;
			mpCapacity = mpStart + newCapacity;
		}
	}

	size_t size() const
	{
		return mpEnd - mpStart;
	}

	T operator[](size_t index) const
	{
		return mpStart[index];
	}

private:
	static T* allocate(size_t numElements)
	{
		cIGZAllocatorServicePtr pAllocator;

		T* ptr = static_cast<T*>(pAllocator->Allocate(numElements * sizeof(T)));

		if (!ptr)
		{
			throw std::bad_alloc();
		}

		return ptr;
	}

	static void deallocate(T* ptr)
	{
		cIGZAllocatorServicePtr pAllocator;

		pAllocator->Deallocate(ptr);
	}

	static void destroy(T& item)
	{
		if constexpr (std::is_pointer_v<T>)
		{
			T ptr = item;

			if (ptr)
			{
				if constexpr (std::is_base_of_v<cIGZUnknown, std::remove_pointer_t<T>>)
				{
					ptr->Release();
				}
				else
				{
					ptr->~T();
				}
			}
		}
		else
		{
			if constexpr (std::is_base_of_v<cIGZUnknown, T>)
			{
				item.Release();
			}
			else
			{
				item.~T();
			}
		}
	}

	static void destroy_contents(T* pItems, size_t itemCount)
	{
		for (size_t i = 0; i < itemCount; i++)
		{
			destroy(pItems[i]);
		}
	}

	size_t remaining_capacity() const
	{
		return mpCapacity - mpEnd;
	}

	T* mpStart;
	T* mpEnd;
	T* mpCapacity;
};