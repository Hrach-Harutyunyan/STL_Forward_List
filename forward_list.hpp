#include <iostream>

namespace my_list 
{
    template <typename T>
    struct node
    {
        T _m_data;
        node* _p_Next;
        node(T data = T(),node* Next = nullptr) : _m_data(data), _p_Next(Next) {};
        ~node() {};
    };

    template <typename T>
    class forward_list
    {
    public:
        void print();

    public:
        forward_list();
        forward_list(T data);
        forward_list(const forward_list&);
        forward_list(forward_list&& other);
        forward_list& operator = (const forward_list&);
        forward_list& operator = (forward_list&& other);
        ~forward_list();       

    public:
        void push_front(T);
        void insert(T, std::size_t);
        void remove_at(std::size_t);
        void clear();
        void pop_front();
        bool hasCycle();
        const node<T>* reverse();
        const node<T>* middleNode();
        const std::size_t& getSize() const {return _m_size;};
        bool empty() const {return (!_m_head);};
        const T& front() const {return _m_head->_m_data;};

    private:
        node<T>* _m_head;
        std::size_t _m_size;
    };


    template <typename T>
    forward_list<T>::forward_list() : _m_head(nullptr),_m_size{} {};

    template <typename T>
    forward_list<T>::~forward_list() { 
        clear();
    };

    template <typename T>
    forward_list<T>::forward_list(T data) : _m_head (new node<T>(data)), _m_size{} { 
        ++ _m_size;
    };

    template <typename T>
    forward_list<T>::forward_list(const forward_list<T>& other) :_m_head(nullptr),_m_size{} {
        if(other.getSize()) {
            node<T>* forCopy = other._m_head;
            node<T>* forPaste = new node<T>(forCopy->_m_data);
            _m_head = forPaste;
            ++_m_size;  
            while (_m_size != other._m_size) {
                forPaste->_p_Next = new node<T>(forCopy->_m_data);
                forPaste = forPaste->_p_Next;
                forCopy = forCopy->_p_Next;  
                ++_m_size;  
            }
            forPaste = nullptr;
            forCopy = nullptr;
        }
    };

    template <typename T>
    forward_list<T>& forward_list<T>::operator = (const forward_list& other) {
        if(this == &other) {
            return *this;
        }
        if(other.getSize()) {
            node<T>* forCopy = other._m_head;
            node<T>* forPaste = new node<T>(forCopy->_m_data);
            _m_head = forPaste;
            ++_m_size;  
            while (_m_size != other._m_size) {
                forPaste->_p_Next = new node<T>(forCopy->_m_data);
                forPaste = forPaste->_p_Next;
                forCopy = forCopy->_p_Next;  
                ++_m_size;  
            }
            forPaste = nullptr;
            forCopy = nullptr;
            return *this;
        }   
    };

    template <typename T>
    forward_list<T>::forward_list(forward_list&& otherList) {
        this->_m_head = otherList._m_head;
        this->_m_size = otherList._m_size;
        otherList._m_head = nullptr;
        otherList._m_size = 0;
    }

    template <typename T>
    forward_list<T>& forward_list<T>::operator=(forward_list<T>&& otherList) {
        if(this == &otherList) {
            return *this;
        }
        this->_m_head = otherList._m_head;
        this->_m_size = otherList._m_size;
        otherList._m_head = nullptr;
        otherList._m_size = 0;
        return *this;
    }

    template <typename T>
    void forward_list<T>::push_front(T data) {
        _m_head = new node<T>(data,_m_head);
        ++_m_size;
    }

    template <typename T>
    void forward_list<T>::pop_front() {
        if(_m_head->_p_Next != nullptr) {
            node<T>* temp = _m_head;
            _m_head = _m_head->_p_Next;
            delete temp;
        } else {
            delete _m_head;
            _m_head = nullptr;
        }
        --_m_size;
    }

    template <typename T>
    void forward_list<T>::insert(T data, std::size_t position) {
        if(position == 0) {
            push_front(data);
        } else if (position > 0) {
            node<T>* prev = _m_head;
            for (int i = 0; i < position - 1; i++) {
                prev = prev->_p_Next;
            }
            prev->_p_Next = new node<T>(data,prev->_p_Next);;
            ++_m_size;            
        }
    }

    template <typename T>
    void forward_list<T>::remove_at(std::size_t position) {
        if(position == 0) {
            pop_front();
        } else if (position > 0) {
            node<T>* prev = _m_head;
            for (int i = 0; i < position - 1; i++) {
                prev = prev->_p_Next;
            }   
            node<T>* toDelete = prev->_p_Next;    
            prev->_p_Next = toDelete->_p_Next;
            delete toDelete;
            --_m_size;   
        }
    }

    template <typename T>
    void forward_list<T>::clear() {
        while (_m_size) {
            pop_front();
        }
    }

    template <typename T>
    const node<T>* forward_list<T>::reverse() {
        if(!_m_head || !_m_head->_p_Next) {
            return _m_head;
        } else {
            node<T>* cur = _m_head->_p_Next;
            node<T>* temp = _m_head;
            while (cur) {
                temp->_p_Next = cur->_p_Next;
                cur->_p_Next = _m_head;
                _m_head = cur;
                cur = temp->_p_Next;
            }
            temp = nullptr;
            cur = nullptr;
            return _m_head;
        }  
    }

    template <typename T>
    void forward_list<T>::print() {
        node<T>* cur = _m_head;
        while (cur) {
            std::cout << cur->_m_data << ", ";
            cur = cur->_p_Next;
        }
        cur = nullptr; 
    }

    template <typename T>
    bool forward_list<T>::hasCycle() {
        if(!_m_head ) {
            return false;
        }
        node<T>*fast = _m_head;
        node<T>*slow = _m_head;
        while(fast!= nullptr && slow != nullptr && fast->_p_Next != nullptr) {
            fast = fast->_p_Next->_p_Next;
            slow = slow->_p_Next;
            if(fast == slow) {
                fast = nullptr;
                slow = nullptr;
                return true;
            }
        }
        fast = nullptr;
        slow = nullptr;
        return false; 
    }

    template <typename T>
    const node<T>* forward_list<T>::middleNode() {
        node<T>* slow = _m_head;
        node<T>* fast = _m_head;
        while(fast != nullptr && fast->_p_Next !=nullptr) {
            slow = slow ->void insert(T, std::size_t);
        void remove_at(std::size_t); _p_Next;
            fast = fast -> _p_Next -> _p_Next;
        }
        return slow;
    };
}