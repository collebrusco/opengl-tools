//
//  pop_vector.h
//  opengl-tools
//
//  Created by Frank Collebrusco on 12/23/22.
//
//

#ifndef pop_vector_h
#define pop_vector_h
#include <vector>

template <typename T>
class pop_vector {
private:
public:
    std::vector<T> vec;
    pop_vector(){}
    bool pop(uint32_t i){
        if (i > (vec.size()-1)){
            return false; // no such item
        }
        if (i == (vec.size()-1)){
            vec.pop_back();
        } else {
//            delete vec.at(i); //DEBUG if these are dynamic pointers, need to delete
            for (int j = i; j < vec.size() - 1; j++){
                vec.at(j) = vec.at(j+1);
            }
            vec.pop_back();
        }
        return true;
    }
};

#endif /* pop_vector_h */
