#ifndef OURHASHMAP_H
#define OURHASHMAP_H

#include<ostream>
#include "vector.h"
#include "error.h"
using namespace std;

template <typename KeyType,typename ValueType>
class OurHashMap{
public:
    OurHashMap();
    ~OurHashMap();

    OurHashMap(OurHashMap& map2);
    OurHashMap& operator=(OurHashMap& map2);

    void clear();
    int size() const;
    bool isEmpty() const;

    void put(const KeyType& key,const ValueType& value);
    bool containsKey(const KeyType& key);
    void remove(const KeyType& key);

    Vector<KeyType> keys() const;
    Vector<ValueType> values() const;

    ValueType& operator[](const KeyType &key);

private:
    struct HashNode{
        KeyType key;
        ValueType value;
        int hashcode=-1;
    };

    HashNode* array;
    int numItems;
    int capacity;

    static const int INITIAL_CAPACITY=64;

    int getHashCode(const KeyType& key) const;
    void rehash();
};

template <typename KeyType,typename ValueType>
const int OurHashMap<KeyType,ValueType>::INITIAL_CAPACITY;

template <typename KeyType,typename ValueType>
OurHashMap<KeyType,ValueType>::OurHashMap(){
    capacity=INITIAL_CAPACITY;
    numItems=0;
    array=new HashNode[capacity];
}

template <typename KeyType,typename ValueType>
OurHashMap<KeyType,ValueType>::~OurHashMap(){
    delete []array;
}

template <typename KeyType,typename ValueType>
OurHashMap<KeyType,ValueType>::OurHashMap(OurHashMap& map2){
    numItems=0;
    capacity=max(INITIAL_CAPACITY,map2.size());
    array=new HashNode[capacity];
    for (auto key_temp:map2.keys()){
        put(key_temp,map2[key_temp]);
    }
}

template <typename KeyType,typename ValueType>
OurHashMap<KeyType, ValueType>& OurHashMap<KeyType,ValueType>::operator=(OurHashMap& map2){
    clear();    /* 这里令numItems为0即可，
                   因为capacity会在put里面自动更新，array已经不需要改动 */
    for (auto key:map2.keys()){
        put(key,map2[key]);
    }
    return *this;
}

template <typename KeyType,typename ValueType>
void OurHashMap<KeyType,ValueType>::clear(){
    for (int i=0;i<capacity;i++){
        array[i].hashcode=-1;
    }
    numItems=0;
}

template <typename KeyType,typename ValueType>
int OurHashMap<KeyType,ValueType>::size() const{
    return numItems;
}

template <typename KeyType,typename ValueType>
bool OurHashMap<KeyType,ValueType>::isEmpty() const{
    return numItems==0;
}

template <typename KeyType,typename ValueType>
Vector<KeyType> OurHashMap<KeyType,ValueType>::keys() const{
   Vector<KeyType> keys;
   for (int i=0;i<capacity;i++){
       if (array[i].hashcode!=-1){
           keys.add(array[i].key);
       }
   }
   return keys;
}

template <typename KeyType,typename ValueType>
Vector<ValueType> OurHashMap<KeyType,ValueType>::values() const{
   Vector<ValueType> values;
   for (int i=0;i<capacity;i++){
       if (array[i].hashcode!=-1){
           values.add(array[i].value);
       }
   }
   return values;
}

template <typename KeyType,typename ValueType>
bool OurHashMap<KeyType,ValueType>::containsKey(const KeyType& key){
    int hashcode=getHashCode(key);
    int idx=hashcode;
    while (true){
        if (array[idx].hashcode==-1){
            return false;
        }
        else if (array[idx].hashcode<hashcode){
            idx=(idx+1)%capacity;
        }
        else if (array[idx].hashcode==hashcode){
            if (array[idx].key==key){
                return true;
            }
            idx=(idx+1)%capacity;
        }
        else{
            return false;
        }
    }
}

template <typename KeyType,typename ValueType>
void OurHashMap<KeyType,ValueType>::put(const KeyType& key,const ValueType& value){
    int hashcode=getHashCode(key);
    int idx=hashcode;
    HashNode newNode{key,value,hashcode};
    while (true){
        if (array[idx].hashcode==-1){
            array[idx]=newNode;
            numItems++;
            if (numItems>capacity*0.5){
                rehash();
            }
            return;
        }
        else if (array[idx].hashcode<hashcode){
            idx=(idx+1)%capacity;
        }
        else if (array[idx].hashcode==hashcode){
            if (array[idx].key==key){
                array[idx].value=value;
                return;
            }
            idx=(idx+1)%capacity;
        }
        else{
            swap(array[idx],newNode);
            idx=(idx+1)%capacity;
        }
    }
}

template <typename KeyType,typename ValueType>
ValueType& OurHashMap<KeyType,ValueType>::operator[](const KeyType &key){
    if (!containsKey(key)){
        put(key,ValueType());
    }
    int hashcode=getHashCode(key);
    int idx=hashcode;
    while (true){
        if (array[idx].hashcode<hashcode){
            idx=(idx+1)%capacity;
        }
        else{
            if (array[idx].key==key){
                return array[idx].value;
            }
            idx=(idx+1)%capacity;
        }
    }
}

template <typename KeyType,typename ValueType>
void OurHashMap<KeyType,ValueType>::remove(const KeyType& key){
    int hashcode=getHashCode(key);
    int idx=hashcode;
    while (true){
        if (array[idx].hashcode==-1){
            return;
        }
        else if (array[idx].hashcode<hashcode){
            idx=(idx+1)%capacity;
        }
        else if (array[idx].hashcode==hashcode){
            if (array[idx].key==key){
                while (array[(idx+1)%capacity].hashcode!=(idx+1)%capacity &&
                       array[(idx+1)%capacity].hashcode!=-1){   /* 这句话很关键 */
                    array[idx]=array[idx+1];
                    idx=(idx+1)%capacity;
                }
                array[idx].hashcode=-1;
                numItems--;
                return;
            }
            idx=(idx+1)%capacity;
        }
        else{
            return;
        }
    }
}

template <typename KeyType,typename ValueType>
void OurHashMap<KeyType,ValueType>::rehash(){
    Vector<HashNode> nodes;
    for (int i=0;i<capacity;i++){
        nodes.add(array[i]);
    }
    delete []array;
    numItems=0;
    capacity*=2;
    array=new HashNode[capacity];
    for (auto node:nodes){
        put(node.key,node.value);
    }

}

template <typename KeyType,typename ValueType>
int OurHashMap<KeyType,ValueType>::getHashCode(const KeyType& key) const{
    return hash<KeyType>{}(key)%capacity;
}

#endif // OURHASHMAP_H
