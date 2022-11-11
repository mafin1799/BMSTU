#pragma once
#ifndef Iterator_h
#define Iterator_h

template<typename K, typename V>
struct S {
    K key;
    V val;
};

template<typename K, typename V>
class Iterator {
private:
    S<K, V>* it;
public:
    Iterator() noexcept;
    Iterator(S<K, V>* element) noexcept;
    Iterator(const Iterator& lcopy);
    Iterator(Iterator&& rcopy) noexcept;
    ~Iterator() noexcept;

    Iterator& operator=(const Iterator& lcopy);
    Iterator& operator=(Iterator&& rcopy) noexcept;
    S<K, V>& operator*();
    S<K, V>* operator->();
    Iterator operator++(int) noexcept;
    Iterator operator--(int) noexcept;
    Iterator& operator++() noexcept;
    Iterator& operator--() noexcept;

    bool operator!=(const Iterator& right) const;
};
template<typename K, typename V>
class constIterator {
private:
    const S<K, V>* it;
public:
    constIterator() noexcept;
    constIterator(S<K, V>* element) noexcept;
    constIterator(const constIterator& lcopy);
    constIterator(constIterator&& rcopy) noexcept;
    ~constIterator() noexcept;


    const S<K, V>& operator*() {
        return *it;
    }
    const S<K, V>* operator->() {
        return &it;
    }
    constIterator operator++(int) noexcept;
    constIterator* operator++() noexcept {
        ++it;
        return this;
    }

    friend bool operator==(const constIterator& left, const constIterator& right) {
        return (*left) == (*right);
    }
    bool operator!=(const constIterator& right) const;
};

#endif /* Iterator_h */

template<typename K, typename V>
Iterator<K, V>::Iterator() noexcept{
    it = nullptr;
}

template<typename K, typename V>
Iterator<K, V>::Iterator(S<K, V>* element) noexcept{
    it = element;
}

template<typename K, typename V>
Iterator<K, V>::Iterator(const Iterator& lcopy){
    it = lcopy.it;
}

template<typename K, typename V>
Iterator<K, V>::Iterator(Iterator&& rcopy) noexcept{
    it = rcopy.it;
}

template<typename K, typename V>
Iterator<K, V>::~Iterator() noexcept {}

template<typename K, typename V>
Iterator<K, V>& Iterator<K, V>::operator=(const Iterator<K, V>& lcopy){
    this->it = lcopy.it;
    lcopy.it = nullptr;
    return this;
}

template<typename K, typename V>
Iterator<K, V>& Iterator<K, V>::operator=(Iterator<K, V>&& rcopy) noexcept{
    this->it = rcopy.it;
    return this;
}

template<typename K, typename V>
S<K, V>& Iterator<K, V>::operator*(){
    return *it;
}

template<typename K, typename V>
S<K, V>* Iterator<K, V>::operator->() {
    return it;
}

template<typename K, typename V>
Iterator<K, V> Iterator<K, V>::operator++(int) noexcept{
    return Iterator<K, V>(it++);
}

template<typename K, typename V>
Iterator<K, V> Iterator<K, V>::operator--(int) noexcept{
    Iterator<K, V>(it--);
}
template<typename K, typename V>
Iterator<K, V>& Iterator<K, V>::operator++() noexcept{
    ++it;
    return *this;
}

template<typename K, typename V>
Iterator<K, V>& Iterator<K, V>::operator--() noexcept{
    --it;
    return *this;
}
template<typename K, typename V>
bool Iterator<K, V>::operator!=(const Iterator& right) const{
    return (this->it != right.it);
}

template<typename K, typename V>
inline constIterator<K, V>::constIterator() noexcept
{
    it = nullptr;
}

template<typename K, typename V>
inline constIterator<K, V>::constIterator(S<K, V>* element) noexcept
{
    it = element;
}

template<typename K, typename V>
inline constIterator<K, V>::constIterator(const constIterator& lcopy)
{
    it = lcopy.it;
}

template<typename K, typename V>
inline constIterator<K, V>::constIterator(constIterator&& rcopy) noexcept
{

}

template<typename K, typename V>
inline constIterator<K, V>::~constIterator() noexcept
{
    it = nullptr;
}

template<typename K, typename V>
inline constIterator<K,V> constIterator<K, V>::operator++(int) noexcept
{
    it++;
    return this;
}

template<typename K, typename V>
inline bool constIterator<K, V>::operator!=(const constIterator& right) const
{
    return 0;
}

