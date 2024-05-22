#pragma once
#include <cstdint>
#include <array>
#include <stdexcept>
#include <algorithm>
#include <string>

template<typename T, uint32_t SIZE>
class CircularBuffer{
private:
    uint32_t m_head;
    uint32_t m_tail;
    uint32_t m_curSize;
    std::array<T, SIZE> m_array{};

private:
    struct Iterator{
        using Category   = std::forward_iterator_tag;
        using Distance   = std::ptrdiff_t;
        using value_type = T;
        using Pointer    = T*;
        using Reference  = T&;

        Iterator(Pointer ptr): m_ptr(ptr){}

        // ++it
        Iterator& operator++(){
            m_ptr++;
            return *this;
        }
        // it++
        Iterator operator++(T){
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        
        // --it
        Iterator& operator--(){
            m_ptr--;
            return *this;
        }
        // it--
        Iterator operator--(T){
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        // Dereference *it
        Reference operator* () const{
            return *m_ptr;
        }

        // it->function()
        Pointer operator->(){
            return m_ptr;
        }

        Reference operator[](int index){
            return *(m_ptr + index);
        }
        bool operator==(const Iterator &obj) const{
            return obj.m_ptr == this->m_ptr;
        }

        bool operator!=(const Iterator &obj) const{
            return obj.m_ptr != this->m_ptr;
        }

        Pointer m_ptr;
    };

public:
    CircularBuffer(): m_head(0), m_tail(0), m_curSize(0) {}
    CircularBuffer(const std::initializer_list<T> &values): m_head(0), m_tail(0), m_curSize(0){
        if(values.size() > SIZE){
            throw std::runtime_error("Invalid size");   
        }
        
        for(auto &val: values){
            this->push_back(val);
        }
    }

    void push_back(T value){
        // update array
        if(m_tail >= SIZE){
            m_tail = 0;
        }
        if(m_tail == m_head && m_curSize > 0){
            m_head++;
            if(m_head >= SIZE){ // head shouldn't excced size 
                m_head = 0;
            }
        }
        // update tail
        m_array.at(m_tail) = value;
        m_tail++;
        // update size
        m_curSize++;
        if(m_curSize > SIZE){
            m_curSize = SIZE;
        }
    }
    void pop(){
        if(isEmpty()){
            throw std::runtime_error("Container is empty!");
        }

        if(m_curSize == 1){
            m_head = m_tail;
            m_curSize--;
            return;
        }
        
        m_head++;
        if(m_head == SIZE){
            m_head = 0;
        }
        m_curSize--;
    }
    T const &head(){
        return m_array[m_head];
    }
    T const &tail(){
        return m_array[m_tail];
    }
    uint32_t const &curSize(){
        return m_curSize;
    }
    bool isEmpty(){
        return m_curSize == 0;
    }

    T& operator[](int idx){
        return m_array[idx];
    }

    Iterator begin(){
        return Iterator(&m_array[m_head]);
    }

    Iterator end(){
        return Iterator(&m_array[m_curSize]);
    }
};