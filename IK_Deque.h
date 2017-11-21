#ifndef _DEQUE_H_
#define _DEQUE_H_

#include "IK_Allocator.h"
#include "IK_Iterator.h"
#include "IK_ReverseIterator.h"
#include "IK_Utility.h"

namespace IK_STL{
	template<class T, class Alloc = allocator<T>>
	class deque;
	namespace DE_ITER{
		//class of deque iterator
		template<class T>
		class dq_iter :public iterator<bidirectional_iterator_tag, T>{
		private:
			template<class T, class Alloc>
			friend class ::IK_STL::deque;
		private:
			//typedef IK_STL::deque<T>* cntrPtr;
			typedef const ::IK_STL::deque<T>* cntrPtr;
			size_t mapIndex_;
			T *cur_;
			cntrPtr container_;
		public:
			dq_iter() :mapIndex_(-1), cur_(0), container_(0){}
			dq_iter(size_t index, T *ptr, cntrPtr container)
				:mapIndex_(index), cur_(ptr), container_(container){}
			dq_iter(const dq_iter& it) 
				:mapIndex_(it.mapIndex_), cur_(it.cur_), container_(it.container_){}
			dq_iter& operator = (const dq_iter& it);
			void swap(dq_iter& it);
			reference operator *(){ return *cur_; }
			const reference operator *()const{ return *cur_; }
			pointer operator ->(){ return &(operator*()); }
			const pointer operator ->()const{ return &(operator*()); }
			dq_iter& operator ++();
			dq_iter operator ++(int);
			dq_iter& operator --();
			dq_iter operator --(int);
			bool operator ==(const dq_iter& it)const;
			bool operator !=(const dq_iter& it)const;
		private:
			T *getBuckTail(size_t mapIndex)const;
			T *getBuckHead(size_t mapIndex)const;
			size_t getBuckSize()const;
		public:
			template<class T>
			friend dq_iter<T> operator + (const dq_iter<T>& it, typename dq_iter<T>::difference_type n);
			template<class T>
			friend dq_iter<T> operator + (typename dq_iter<T>::difference_type n, const dq_iter<T>& it);
			template<class T>
			friend dq_iter<T> operator - (const dq_iter<T>& it, typename dq_iter<T>::difference_type n);
			template<class T>
			friend dq_iter<T> operator - (typename dq_iter<T>::difference_type n, const dq_iter<T>& it);
			template<class T>
			friend typename dq_iter<T>::difference_type operator - (const dq_iter<T>& it1, const dq_iter<T>& it2);
			template<class T>
			friend void swap(dq_iter<T>& lhs, dq_iter<T>& rhs);
		};
	}// end of DE_ITER namespace



	//class of deque
	template<class T, class Alloc>
	class deque{
	private:
		template<class T>
		friend class ::IK_STL::DE_ITER::dq_iter;
	public:
		typedef T value_type;
		typedef DE_ITER::dq_iter<T> iterator;
		typedef DE_ITER::dq_iter<const T> const_iterator;
		typedef T& reference;
		typedef const reference const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef Alloc allocator_type;
	private:
		typedef Alloc dataAllocator;
		enum class EBucksSize{BUCKSIZE = 64};
	private:
		iterator beg_, end_;
		size_t mapSize_;
		T **map_;
	public:
		deque();
		explicit deque(size_type n, const value_type& val = value_type());
		template <class InputIterator>
		deque(InputIterator first, InputIterator last);
		deque(const deque& x);

		~deque();

		deque& operator= (const deque& x);
		deque& operator= (deque&& x);

		iterator begin();
		iterator end();
		iterator begin()const;
		iterator end()const;
	public:
		size_type size() const{ return end() - begin(); }
		bool empty() const{ return begin() == end(); }

		reference operator[] (size_type n);
		reference front();
		reference back();
		const_reference operator[] (size_type n) const;
		const_reference front() const;
		const_reference back() const;

		void push_back(const value_type& val);
		void push_front(const value_type& val);
		void pop_back();
		void pop_front();
		void swap(deque& x);
		void clear();
	private:
		T *getANewBuck();
		T** getANewMap(const size_t size);
		size_t getNewMapSize(const size_t size);
		size_t getBuckSize()const;
		void init();
		bool back_full()const;
		bool front_full()const;
		void deque_aux(size_t n, const value_type& val, std::true_type);
		template<class Iterator>
		void deque_aux(Iterator first, Iterator last, std::false_type);
		void reallocateAndCopy();
	public:
		template <class T, class Alloc>
		friend bool operator== (const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs);
		template <class T, class Alloc>
		friend bool operator!= (const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs);
		template <class T, class Alloc>
		friend void swap(deque<T, Alloc>& x, deque<T, Alloc>& y);
	};//end of deque


	namespace DE_ITER {
		template<class T>
		dq_iter<T>& dq_iter<T>::operator ++() {
			if (cur_ != getBuckTail(mapIndex_))//+1后还在同一个桶里
				++cur_;
			else if (mapIndex_ + 1 < container_->mapSize_) {//+1后还在同一个map里
				++mapIndex_;
				cur_ = getBuckHead(mapIndex_);
			}
			else {//+1后跳出了map
				mapIndex_ = container_->mapSize_;
				//cur_ = container_->map_[mapIndex_] + getBuckSize();//指向map_[mapSize_-1]的尾的下一个位置
				cur_ = container_->map_[mapIndex_];
			}
			return *this;
		}
		template<class T>
		dq_iter<T> dq_iter<T>::operator ++(int) {
			auto res = *this;
			++(*this);
			return res;
		}
		template<class T>
		dq_iter<T>& dq_iter<T>::operator --() {
			if (cur_ != getBuckHead(mapIndex_))//当前不指向桶头
				--cur_;
			else if (mapIndex_ - 1 >= 0) {//-1后还在map里面
				--mapIndex_;
				cur_ = getBuckTail(mapIndex_);
			}
			else {
				mapIndex_ = 0;
				cur_ = container_->map_[mapIndex_];//指向map_[0]的头
			}
			return *this;
		}
		template<class T>
		dq_iter<T> dq_iter<T>::operator --(int) {
			auto res = *this;
			--(*this);
			return res;
		}
		template<class T>
		bool dq_iter<T>::operator ==(const dq_iter& it)const {
			return ((mapIndex_ == it.mapIndex_) &&
				(cur_ == it.cur_) && (container_ == it.container_));
		}
		template<class T>
		bool dq_iter<T>::operator !=(const dq_iter<T>& it)const {
			return !(*this == it);
		}
		template<class T>
		dq_iter<T>& dq_iter<T>::operator = (const dq_iter& it) {
			if (this != &it) {
				mapIndex_ = it.mapIndex_;
				cur_ = it.cur_;
				container_ = it.container_;
			}
			return *this;
		}
		template<class T>
		void dq_iter<T>::swap(dq_iter& it) {
			IK_STL::swap(mapIndex_, it.mapIndex_);
			IK_STL::swap(cur_, it.cur_);
			//IK_STL::swap(container_, it.container_);
		}
		template<class T>
		dq_iter<T> operator + (const dq_iter<T>& it, typename dq_iter<T>::difference_type n) {//assume n >= 0
			dq_iter<T> res(it);
			auto m = res.getBuckTail(res.mapIndex_) - res.cur_;
			if (n <= m) {//前进n步仍在同一个桶中
				res.cur_ += n;
			}
			else {
				n = n - m;
				res.mapIndex_ += (n / it.getBuckSize() + 1);
				auto p = res.getBuckHead(res.mapIndex_);
				auto x = n % it.getBuckSize() - 1;
				res.cur_ = p + x;
			}
			return res;
		}
		template<class T>
		dq_iter<T> operator + (typename dq_iter<T>::difference_type n, const dq_iter<T>& it) {
			return (it + n);
		}
		template<class T>
		dq_iter<T> operator - (const dq_iter<T>& it, typename dq_iter<T>::difference_type n) {//assume n >= 0
			dq_iter<T> res(it);
			auto m = res.cur_ - res.getBuckHead(res.mapIndex_);
			if (n <= m)//后退n步还在同一个桶中
				res.cur_ -= n;
			else {
				n = n - m;
				res.mapIndex_ -= (n / res.getBuckSize() + 1);
				res.cur_ = res.getBuckTail(res.mapIndex_) - (n % res.getBuckSize() - 1);
			}
			return res;
		}
		template<class T>
		dq_iter<T> operator - (typename dq_iter<T>::difference_type n, const dq_iter<T>& it) {
			return (it - n);
		}
		template<class T>
		typename dq_iter<T>::difference_type operator - (const dq_iter<T>& it1, const dq_iter<T>& it2) {
			if (it1.container_ == it2.container_ && it1.container_ == 0)
				return 0;
			return typename dq_iter<T>::difference_type(it1.getBuckSize()) * (it1.mapIndex_ - it2.mapIndex_ - 1)
				+ (it1.cur_ - it1.getBuckHead(it1.mapIndex_)) + (it2.getBuckTail(it2.mapIndex_) - it2.cur_) + 1;
		}
		template<class T>
		void swap(dq_iter<T>& lhs, dq_iter<T>& rhs) {
			lhs.swap(rhs);
		}
		template<class T>
		T *dq_iter<T>::getBuckTail(size_t mapIndex)const {
			return container_->map_[mapIndex] + (container_->getBuckSize() - 1);
		}
		template<class T>
		T *dq_iter<T>::getBuckHead(size_t mapIndex)const {
			return container_->map_[mapIndex];
		}
		template<class T>
		size_t dq_iter<T>::getBuckSize()const {
			return container_->getBuckSize();
		}
	}//end of DE_ITER namespace

	template<class T, class Alloc>
	bool deque<T, Alloc>::back_full()const {
		return map_[mapSize_ - 1] && (map_[mapSize_]) == end().cur_;
	}
	template<class T, class Alloc>
	bool deque<T, Alloc>::front_full()const {
		return map_[0] && map_[0] == begin().cur_;
	}
	template<class T, class Alloc>
	void deque<T, Alloc>::deque_aux(size_t n, const value_type& val, std::true_type) {
		int i = 0;
		for (; i != n / 2; ++i)
			(*this).push_front(val);
		for (; i != n; ++i)
			(*this).push_back(val);
	}
	template<class T, class Alloc>
	template<class Iterator>
	void deque<T, Alloc>::deque_aux(Iterator first, Iterator last, std::false_type) {
		difference_type mid = (last - first) / 2;
		for (auto it = first + mid; it != first - 1; --it)
			(*this).push_front(*it);
		for (auto it = first + mid + 1; it != last; ++it)
			(*this).push_back(*it);
	}
	template<class T, class Alloc>
	void deque<T, Alloc>::init() {
		mapSize_ = 2;
		map_ = getANewMap(mapSize_);
		beg_.container_ = end_.container_ = this;
		beg_.mapIndex_ = end_.mapIndex_ = mapSize_ - 1;
		beg_.cur_ = end_.cur_ = map_[mapSize_ - 1];
	}
	template<class T, class Alloc>
	T *deque<T, Alloc>::getANewBuck() {
		return dataAllocator::allocate(getBuckSize());
	}
	template<class T, class Alloc>
	T** deque<T, Alloc>::getANewMap(const size_t size) {
		T **map = new T*[size];
		for (int i = 0; i != size; ++i)
			map[i] = getANewBuck();
		return map;
	}
	template<class T, class Alloc>
	size_t deque<T, Alloc>::getNewMapSize(const size_t size) {
		return (size == 0 ? 2 : size * 2);
	}
	template<class T, class Alloc>
	size_t deque<T, Alloc>::getBuckSize()const {
		return (size_t)EBucksSize::BUCKSIZE;
	}
	template<class T, class Alloc>
	void deque<T, Alloc>::clear() {
		/*for (int i = 0; i != mapSize_; ++i)
		if (!map_[i])
		dataAllocator::destroy(map_[i], map_[i] + getBuckSize());*/
		for (auto i = 0; i != mapSize_; ++i) {
			for (auto p = map_[i] + 0; !p && p != map_[i] + getBuckSize(); ++p)
				dataAllocator::destroy(p);
		}
		mapSize_ = 0;
		beg_.mapIndex_ = end_.mapIndex_ = mapSize_ / 2;
		beg_.cur_ = end_.cur_ = map_[mapSize_ / 2];
	}
	template<class T, class Alloc>
	typename deque<T, Alloc>::reference deque<T, Alloc>::operator[] (size_type n) {
		return *(begin() + n);
	}
	template<class T, class Alloc>
	typename deque<T, Alloc>::reference deque<T, Alloc>::front() {
		return *begin();
	}
	template<class T, class Alloc>
	typename deque<T, Alloc>::reference deque<T, Alloc>::back() {
		return *(end() - 1);
	}
	//由于const迭代器的设计失误故以下三个const函数会丧失const特性
	template<class T, class Alloc>
	typename deque<T, Alloc>::const_reference deque<T, Alloc>::operator[] (size_type n) const {
		return *(begin() + n);
	}
	template<class T, class Alloc>
	typename deque<T, Alloc>::const_reference deque<T, Alloc>::front() const {
		return *begin();
	}
	template<class T, class Alloc>
	typename deque<T, Alloc>::const_reference deque<T, Alloc>::back() const {
		return *(end() - 1);
	}
	template<class T, class Alloc>
	typename deque<T, Alloc>::iterator deque<T, Alloc>::begin() { return beg_; }
	template<class T, class Alloc>
	typename deque<T, Alloc>::iterator deque<T, Alloc>::end() { return end_; }
	//迭代器设计失误，会使下面两个函数丧失const特性，暂时没有效解决办法故只能先这样妥协
	template<class T, class Alloc>
	typename deque<T, Alloc>::iterator deque<T, Alloc>::begin()const { return beg_; }
	template<class T, class Alloc>
	typename deque<T, Alloc>::iterator deque<T, Alloc>::end()const { return end_; }
	template<class T, class Alloc>
	deque<T, Alloc>::~deque() {
		for (int i = 0; i != mapSize_; ++i) {
			for (auto p = map_[i] + 0; !p && p != map_[i] + getBuckSize(); ++p)
				dataAllocator::destroy(p);
			if (!map_[i])
				dataAllocator::deallocate(map_[i], getBuckSize());
		}
		delete[] map_;
	}
	template<class T, class Alloc>
	deque<T, Alloc>::deque()
		:mapSize_(0), map_(0) {}
	template<class T, class Alloc>
	deque<T, Alloc>::deque(size_type n, const value_type& val = value_type()) {
		deque();
		deque_aux(n, val, typename std::is_integral<size_type>::type());
	}
	template<class T, class Alloc>
	template <class InputIterator>
	deque<T, Alloc>::deque(InputIterator first, InputIterator last) {
		deque();
		deque_aux(first, last, typename std::is_integral<InputIterator>::type());
	}
	template<class T, class Alloc>
	deque<T, Alloc>::deque(const deque& x) {
		mapSize_ = x.mapSize_;
		map_ = getANewMap(mapSize_);
		for (int i = 0; i + x.beg_.mapIndex_ != x.mapSize_; ++i)
			for (int j = 0; j != getBuckSize(); ++j)
				map_[x.beg_.mapIndex_ + i][j] = x.map_[x.beg_.mapIndex_ + i][j];
		beg_.mapIndex_ = x.beg_.mapIndex_;
		end_.mapIndex_ = x.end_.mapIndex_;
		beg_.cur_ = map_[beg_.mapIndex_] + (x.beg_.cur_ - x.map_[x.beg_.mapIndex_]);
		end_.cur_ = map_[end_.mapIndex_] + (x.end_.cur_ - x.map_[x.end_.mapIndex_]);
		beg_.container_ = end_.container_ = this;
	}
	template<class T, class Alloc>
	void deque<T, Alloc>::reallocateAndCopy() {
		auto newMapSize = getNewMapSize(mapSize_);
		T** newMap = getANewMap(newMapSize);
		size_t startIndex = newMapSize / 4;
		for (int i = 0; i + beg_.mapIndex_ != mapSize_; ++i)
			for (int j = 0; j != getBuckSize(); ++j)
				newMap[startIndex + i][j] = map_[beg_.mapIndex_ + i][j];

		size_t n = beg_.cur_ - map_[beg_.mapIndex_];
		auto size = this->size();
		auto b = beg_, e = end_;
		clear();
		mapSize_ = newMapSize;
		map_ = newMap;
		beg_ = iterator(startIndex, newMap[startIndex] + n, this);
		end_ = beg_ + size;

	}
	template<class T, class Alloc>
	void deque<T, Alloc>::push_back(const value_type& val) {
		if (empty()) {
			init();
		}
		else if (back_full()) {
			reallocateAndCopy();
		}
		//*end_ = val;
		//bug fix
		//2015.01.02
		IK_STL::construct(end_.cur_, val);
		++end_;
	}
	template<class T, class Alloc>
	void deque<T, Alloc>::push_front(const value_type& val) {
		if (empty()) {
			init();
		}
		else if (front_full()) {
			reallocateAndCopy();
		}
		--beg_;
		//*beg_ = val;
		//bug fix
		//2015.01.02
		IK_STL::construct(beg_.cur_, val);
	}
	template<class T, class Alloc>
	void deque<T, Alloc>::pop_front() {
		dataAllocator::destroy(beg_.cur_);
		++beg_;
	}
	template<class T, class Alloc>
	void deque<T, Alloc>::pop_back() {
		--end_;
		dataAllocator::destroy(end_.cur_);
	}
	template<class T, class Alloc>
	void deque<T, Alloc>::swap(deque<T, Alloc>& x) {
		IK_STL::swap(mapSize_, x.mapSize_);
		IK_STL::swap(map_, x.map_);
		beg_.swap(x.beg_);
		end_.swap(x.end_);
	}

	template <class T, class Alloc>
	bool operator== (const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs) {
		auto cit1 = lhs.begin(), cit2 = rhs.begin();
		for (; cit1 != lhs.end() && cit2 != rhs.end(); ++cit1, ++cit2) {
			if (*cit1 != *cit2)
				return false;
		}
		if (cit1 == lhs.end() && cit2 == rhs.end())
			return true;
		return false;
	}
	template <class T, class Alloc>
	bool operator!= (const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs) {
		return !(lhs == rhs);
	}
	template <class T, class Alloc>
	void swap(deque<T, Alloc>& x, deque<T, Alloc>& y) {
		x.swap(y);
	}
}


#endif