#pragma once

//RAII
/*template<class T>
class AutoPtr {
public:
	//RAII
	AutoPtr(T* ptr)
		:_ptr(ptr)
	{}
	~AutoPtr()
	{
		printf("ptr:0x%p\n", _ptr);
		delete _ptr;
	}
	//像指针一样
	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
protected:
	T * _ptr;
};*/

//1.auto_ptr-->管理权转移
template<class T>
class AutoPtr {
public:
	//RAII
	AutoPtr(T* ptr)
		:_ptr(ptr)
	{}
	~AutoPtr()
	{
		printf("ptr:0x%p\n", _ptr);
		delete _ptr;
	}
	AutoPtr(AutoPtr<T>& ap)
	{
		_ptr = ap._ptr;
		ap._ptr = NULL;
	}
	AutoPtr<T>& operator=(AutoPtr<T>& ap)
	{
		if (this != &ap)
		{
			delete _ptr;
			_ptr = ap._ptr;
			ap._ptr = NULL;
		}
		return *this;
	}
	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
protected:
	T* _ptr;
};

//2.scoped_ptr-->防拷贝
template<class T>
class ScopedPtr {
public:
	ScopedPtr(T* ptr)
		:_ptr(ptr)
	{}
	~ScopedPtr()
	{
		printf("ptr:0x%p\n", _ptr);
		delete _ptr;
	}
	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
protected:
	T * _ptr;
	ScopedPtr(const ScopedPtr<T>& sp)//拷贝构造函数定义为私有的
	{}
};

//3.shared_ptr-->引用计数
template<class T>
class SharedPtr {
public:
	SharedPtr(T* ptr)
		:_ptr(ptr)
		, _Pcount(new int(1))
	{}
	~SharedPtr()
	{
		if (--(*_Pcount)==0)
		{
			printf("ptr:0x%p\n", _ptr);
			delete _ptr;
			delete _Pcount;
		}
	}
	T& operator*()
	{
		return *_ptr;
	}
	SharedPtr(const SharedPtr<T>& sp)
	{
		_Pcount = sp._Pcount;
		(*_Pcount)++;
		_ptr = sp._ptr;
	}
	SharedPtr<T>& operator=(const SharedPtr<T>& sp)
	{
		if (this != &sp)
		{
			if (--(*_Pcount) == 0)
			{
				delete _Pcount;
				delete _ptr;
			}
			_Pcount = sp._Pcount;
			++(*_Pcount);
			_ptr = sp._ptr;
		}
		return *this;
	}
protected:
	T* _ptr;
	int* _Pcount;
};