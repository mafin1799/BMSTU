#include <string>
#include <sstream>
#include "iterator.h"

template<typename K, typename V>
class Map {
private:
    S<K, V>* _data;
    std::size_t _size;

public:
    Map() noexcept;
    Map(const Map<K, V>&) noexcept;
    Map(Map<K, V>&&) noexcept;
    ~Map();

    std::size_t size() const;
    void push(K, V);
    void remove(K) noexcept;
    Iterator<K, V> find(const K);
    constIterator<K, V> find(const K) const;
    void Clear();
    std::string* keys() const;
    std::string toJSON() const;

    V& at(K);
    const V at(K) const;
    V& operator[](K key);
    const V operator[](K key) const;
    Map<K, V>& operator=(const S<K, V>* mdata);
    Map<K, V>& operator=(const Map<K, V>& map2);

    Iterator<K, V> begin();
    Iterator<K, V> end();

    constIterator<K, V> begin() const;
    constIterator<K, V> end() const;
};

// ----- CTORS -----

template<typename K, typename V>    // *
Map<K, V>::Map() {
    _data = new S<K, V>[1];
    _size = 1;
}

template<typename K, typename V>    // *
Map<K, V>::Map(const Map<K, V>& m) noexcept {
    _size = m._size;
    _data = new S<K, V>[_size];
    for (int i = 0; i < _size; i++) {
        _data[i].key = m._data[i].key;
        _data[i].val = m._data[i].val;
    }
}

template<typename K, typename V>    // *
Map<K, V>::Map(Map<K, V>&& m) noexcept {
    _size = m._size;
    _data = m._data;
    m._data = nullptr;
}

template<typename K, typename V>    // *
Map<K, V>::~Map(){
    delete[] _data;
}


// ----- METHODS ----- //

template<typename K, typename V>
std::size_t Map<K, V>::size() const {
    return _size-1;
}

template<typename K, typename V>
void Map<K, V>::push(K nkey, V nval) {
    for (int i = 0; i < _size-1; i++) {
        if (_data[i].key == nkey) {
            _data[i].val = nval;
            return;
        }
    }
    auto* _ndata = new S<K, V>[_size+1];
    for (int i = 0; i < _size-1; i++) {
        _ndata[i] = _data[i];
    }
    delete[] _data;
    _data = _ndata;
    _data[_size-1].key = nkey;
    _data[_size-1].val = nval;
    _size++;
}

template<typename K, typename V>
void Map<K, V>::remove(K kek) noexcept {
    if (_size > 1) {
        int key = -1;
        for (int i = 0; i < _size-1; i++){
            if (_data[i].key == kek) {
                key = i;
                break;
            }
        }
        if (key < 0) return;

        S<K, V>* _ndata = new S<K, V>[_size-1];
        for (int i = 0, b = 0; i < _size-1; i++) {
            if (key == i) {
                b++;
                continue;
            }
            _ndata[i-b] = _data[i];
        }
        _size--;
        delete[] _data;
        _data = _ndata;
    }
}

template<typename K, typename V>
Iterator<K, V> Map<K, V>::find(const K _key){
    Iterator<K, V> in(_data);
    while (in != this->end()) {
        if((*in).key == _key) {
            return in;
        }
        in++;
    }
    return this->end();
}

template<typename K, typename V>
constIterator<K, V> Map<K, V>::find(const K _key) const{
    constIterator<K, V> in(_data);
    while (in != this->end()) {
        if ((*in).key == _key) {
            return in;
        }
        in++;
    }
    return this->end();
}

template<typename K, typename V>
void Map<K, V>::Clear() {
    if (_data != nullptr) {
        delete[] _data;
        _data = nullptr;
    }
    _size = 0;
}

template<typename K, typename V>
V& Map<K, V>::at(K kkey) {
    for (int i = 0; i < _size-1; i++){
        if (_data[i].key == kkey){
            return _data[i].val;
        }
    }
    return _data[0].val;//throw
}

template<typename K, typename V>
const V Map<K, V>::at(K kkey) const {
    for (int i = 0; i < _size-1; i++) {
        if (_data[i].key == kkey) {
            return _data[i].val;
        }
    }
    return _data[0].val;
}

template<typename K, typename V>
std::string Map<K, V>::toJSON() const {
    std::stringstream _str;
    if (_data != nullptr) {
        _str << "{\n";
        for (int i = 0; i < _size; i++) {
            _str << "\t" << _data[i].key<<":" << _data[i].val << ";\n";
        }
        _str << "}";
    }
    return _str.str();
}

template<typename K, typename V>
std::string* Map<K, V>::keys() const {
    std::string* _str = new std::string[_size];//vector
    for (int i = 0; i < _size; i++){
        _str[i] = _data[i].key;
    }
    return _str;
}

template<typename K, typename V>
V& Map<K, V>::operator[](K key) {
    return at(key);//
}

template<typename K, typename V>
const V Map<K, V>::operator[](K key) const{
    return at(key);//
}

template<typename K, typename V>
Map<K, V>& Map<K, V>::operator=(const S<K, V>* mdata) {
    this->_data = mdata;
}

template<typename K, typename V>
Map<K, V>& Map<K, V>::operator=(const Map<K, V>& map2) {
    return Map<K, V>(&map2);
}

template<typename K, typename V>
Iterator<K, V> Map<K, V>::begin() {
    return Iterator<K, V>(_data);
}

template<typename K, typename V>
Iterator<K, V> Map<K, V>::end() {
    return Iterator<K, V>(&_data[_size-1]);
}

template<typename K, typename V>
constIterator<K, V> Map<K, V>::begin() const {
    return constIterator<K, V>(_data);
}
template<typename K, typename V>
constIterator<K, V> Map<K, V>::end() const {
    return constIterator<K, V>(&_data[_size-1]);
}