//
//  ObjectPool.h
//  opengl-tools
//
//  Created by Frank Collebrusco on 1/2/23.
//
//

#ifndef ObjectPool_h
#define ObjectPool_h
#include <stdint.h>

template <class T>
class ObjectPool {
private:
    struct Obj {
        T obj;
        bool active;
        Obj(){
            active = false;
        }
    };
    Obj* pool;
    uint32_t _size;
    uint32_t active_count;
    uint32_t findEmptyIdx(){
        assert(!isFull());
        for (uint32_t i = 0; i < _size; i++){
            if (!pool[i].active){
                return i;
            }
        }
        return -1;
    }
public:
    ObjectPool(uint32_t s){
        _size = s;
        pool = new Obj[_size];
        active_count = 0;
    }
    bool isFull(){
        return active_count == _size;
    }
    T const& operator[](uint32_t i) const {
        assert(i < _size);
        assert(pool[i].active);
        return pool[i].obj;
    }
    T& operator[](uint32_t i)  {
        assert(i < _size);
        assert(pool[i].active);
        return pool[i].obj;
    }
    uint32_t size(){
        return _size;
    }
    uint32_t push(T o){
        uint32_t i = this->findEmptyIdx();
        pool[i].obj = o;
        pool[i].active = true;
        active_count++;
        return i;
    }
    void pop(uint32_t i){
        assert(pool[i].active);
        pool[i].active = false;
        active_count--;
    }
    void force(T o, uint32_t i){
        assert(i < _size);
        pool[i].obj = o;
        if (!pool[i].active){
            pool[i].active = true;
            active_count++;
        }
    }
    ~ObjectPool(){
        delete [] pool;
    }
};

#endif /* ObjectPool_h */
