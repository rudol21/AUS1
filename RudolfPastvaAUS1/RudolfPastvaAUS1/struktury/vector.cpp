#include "vector.h"
#include "ds_routines.h"
#include <cstdlib>
#include <cstring>

namespace structures {

	Vector::Vector(size_t size) :
		memory_(calloc(size, 1)),
		size_(size)
	{
	}

	Vector::Vector(const Vector& other) :
		Vector(other.size_)
	{
		memory_ = memcpy(memory_, other.memory_, size_);
		//throw std::exception("Vector::Vector: Not implemented yet.");
	}

	Vector::~Vector()
	{
		free(memory_);
		memory_ = nullptr;
		size_ = 0;
	}


	Structure* Vector::clone() const
	{
		return new Vector(*this);
	}

	size_t Vector::size() const
	{
		return size_;
	}

	Structure & Vector::operator=(const Structure & other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Vector&>(other);
		}
		return *this;
	}

	Vector& Vector::operator=(const Vector& other)
	{
		if (this != &other)
		{
			size_ = other.size_;
			memory_ = realloc(memory_, size_);
			memory_ = memcpy(memory_, other.memory_, size_);
		}
		return *this;
		//throw std::exception("Vector::operator=: Not implemented yet.");
	}

	bool Vector::operator==(const Vector& other) const
	{
		return size_ == other.size_ && memcpy(memory_, other.memory_, size_) == 0;
		//throw std::exception("Vector::operator==: Not implemented yet.");
	}

	byte& Vector::operator[](const int index)//vracia odkazom
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index in Vector!");
		return *(reinterpret_cast<byte*>(memory_) + index);//pretypujem vector nech to je smernik na byte a posuniem o index lebo neviem velkost void*
	}

	byte Vector::operator[](const int index) const //vracia hodnotou
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index in Vector!");
		return *(reinterpret_cast<byte*>(memory_) + index);
	}

	byte& Vector::readBytes(const int index, const int count, byte& dest)
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index!");
		DSRoutines::rangeCheckExcept(index + count - 1, size_, "Invalid index!"); //potialto 
		memcpy(&dest, getBytePointer(index), count);
		return dest;//opytaj sa na toto
		/*DSRoutines::rangeCheckExcept(index + count, size_ + 1, "Invalid index in Vector!");
		DSRoutines::rangeCheckExcept(dest, size_, "Invalid index in Vector!");
		/*if (this->getBytePointer(index) > &dest &&  &dest.getBytePointer(count) > this->getBytePointer(index) || this->getBytePointer(index + count) > (&dest + count) && (&dest + count) > this->getBytePointer(index + count) || &dest == this->getBytePointer(index))
		{memmove(&dest, this->getBytePointer(index), count);
		}
		else
		{
			memcpy(&dest, this->getBytePointer(index), count);
		}
		return dest;*/

	}

	void Vector::copy(const Vector& src, const int srcStartIndex, Vector& dest, const int destStartIndex, const int length)
	{
		DSRoutines::rangeCheckExcept(srcStartIndex, src.size_, "Invalid src index!");
		DSRoutines::rangeCheckExcept(srcStartIndex + length - 1, src.size_, "Invalid src index!");
		DSRoutines::rangeCheckExcept(destStartIndex, dest.size_, "Invalid dest index!");
		DSRoutines::rangeCheckExcept(destStartIndex + length - 1, src.size_, "Invalid dest index!");
		if ((&src == &dest) && (((srcStartIndex >= destStartIndex) && (srcStartIndex < destStartIndex + length)) || destStartIndex >= srcStartIndex) && (destStartIndex < srcStartIndex + length))
		{
			memcpy(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
		else
		{
			memmove(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}


	}

	byte* Vector::getBytePointer(const int index) const//vracia smernik cize bez*
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index in Vector!");
		return (reinterpret_cast<byte*>(memory_) + index);
	}

}