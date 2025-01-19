#include <iostream>
#include "StrIterator.h"

class Str
{
    private:

    size_t size;
    char* data;

    public:
    //No Position
    static const size_t npos = -1;

    //Constructor and Destructors
    Str(); //Empty String Constructor
    Str(char c); //Char Constructor
    Str(const char* data); //C-string constructor
    Str(const Str& obj); //Copy Constructor
    Str(const Str &obj, size_t position, size_t length = Str::npos); //Substring Constructor
    Str(const char* data, size_t n); //Buffer Constructor
    Str(size_t n, char c); //Fill Constructor
    ~Str(); //Destructor

    //Assignment
    Str& operator=(const char* s);
    Str& operator=(const Str &obj);
    Str& operator=(const char c);

    //Concatenation
    Str operator+(const Str &obj);
    Str operator+(const char* s);
    Str operator+(const char c);
    void operator+=(const Str &obj);
    void operator+=(const char* s);
    void operator+=(const char c);

    //Appending
    Str& append(const Str &obj);
    Str& append(const Str &obj, size_t subpos, size_t sublen);
    Str& append(const char* s);
    Str& append(const char* s, size_t n);
    Str& append(size_t n, char c);

    void push_back(char c);

    //Comparing Operators
    bool operator==(const Str &obj);
    bool operator==(const char* s);
    bool operator!=(const Str &obj);
    bool operator!=(const char* s);
    bool operator<(const Str &obj);
    bool operator<(const char* s);
    bool operator>(const Str &obj);
    bool operator>(const char* s);
    bool operator<=(const Str &obj);
    bool operator<=(const char* s);
    bool operator>=(const Str &obj);
    bool operator>=(const char* s);

    //Access method
    const char operator[](size_t index);
    const char at(size_t index);
    char& back();
    char& front();

    //Insertion and Extraction
    friend std::ostream& operator<<(std::ostream& os, const Str& obj);
    friend std::istream& operator>>(std::istream& is, Str& obj);
    friend std::istream& s_getline(std::istream& is, Str &obj, char delimiter);

    //Range-Based For Loop
    StrIterator begin();
    StrIterator end();

    //Substring
    Str substr(size_t index, size_t length);

    //Finding
    size_t find(const char* s, size_t index = 0);
    size_t find(const Str &obj, size_t index = 0);

    //Removing Functions
    Str erase(size_t index, size_t length);
    Str& clear();

    //Controlling that the string is empty or not
    bool empty();

    //Length
    size_t length();
};

size_t lengthOfCstr(const char* s);

Str::Str()
{
    size = 0;
    data = nullptr;
}

Str::Str(char c)
{
    size = 1;
    data = new char[2];

    data[0] = c;
    data[1] = '\0';
}

Str::Str(const char *data)
{
    size = lengthOfCstr(data);
    this->data = new char[size + 1];

    for (size_t i = 0; i < size; i++)
        this->data[i] = data[i];

    this->data[size] = '\0';
}

Str::Str(const Str& obj) {
    size = obj.size;
    data = new char[size + 1];

    for (size_t i = 0; i < size; i++)
        data[i] = obj.data[i];

    data[size] = '\0';
}

Str::Str(const Str &obj, size_t position, size_t length)
{
    if(length == Str::npos)
    {
        length = obj.size - position;
    }

    size = length;
    data = new char[size + 1];

    for(size_t i = 0; i < length; i++)
        data[i] = obj.data[i + position];

    data[size] = '\0';
}

Str::Str(const char *data, size_t n)
{
    size = n;
    this->data = new char[size + 1];

    for (size_t i = 0; i < size; i++)
        this->data[i] = data[i];

    this->data[size] = '\0';
}

Str::Str(size_t n, char c)
{
    size = n;
    data = new char[size + 1];

    for(size_t i = 0; i < size; i++)
        data[i] = c;

    data[size] = '\0';
}

Str::~Str()
{
    if(this->data != nullptr)
    {
        delete[] data;
        data = nullptr;
        size = 0;
    }
}

Str &Str::operator=(const char *s)
{
    if(this->data != nullptr)
        delete[] this->data;

    this->size = 0;

    this->size = lengthOfCstr(s);

    this->data = new char[this->size + 1];
    for(size_t i = 0; i < this->size; i++)
    {
        this->data[i] = s[i];
    }

    this->data[this->size] = '\0';

    return *this;
}

Str &Str::operator=(const Str &obj)
{
    if(this->data != nullptr)
        delete[] this->data;

    this->size = 0;

    this->size = obj.size;

    this->data = new char[this->size + 1];
    for(size_t i = 0; i < this->size; i++)
    {
        this->data[i] = obj.data[i];
    }

    this->data[this->size] = '\0';

    return *this;
}

Str &Str::operator=(const char c)
{
    if(this->data != nullptr)
        delete[] this->data;

    this->size = 1;

    data = new char[size + 1];

    data[0] = c;
    data[1] = '\0';

    return *this;
}

Str Str::operator+(const Str &obj)
{
    size_t newSize = size + obj.size;

    char* newData = new char[newSize + 1];

    for(size_t i = 0; i < size; i++)
        newData[i] = data[i];

    for(size_t i = 0; i < obj.size; i++)
        newData[size + i] = obj.data[i];

    newData[newSize] = '\0';

    Str s = newData;

    delete[] newData;
    
    return s;
}

Str Str::operator+(const char *s)
{
    size_t newSize = size + lengthOfCstr(s);

    char* newData = new char[newSize + 1];

    for(size_t i = 0; i < size; i++)
        newData[i] = data[i];

    for(size_t i = 0; i < lengthOfCstr(s); i++)
        newData[size + i] = s[i];

    newData[newSize] = '\0';

    Str obj = newData;

    delete[] newData;
    
    return obj;
}

Str Str::operator+(const char c)
{
    size_t newSize = size + 1;

    char* newData = new char[newSize + 1];

    for(size_t i = 0; i < size; i++)
        newData[i] = data[i];

    newData[size] = c;

    newData[newSize] = '\0';

    Str obj = newData;

    delete[] newData;
    
    return obj;
}

void Str::operator+=(const Str &obj)
{
    *this = *this + obj;
}

void Str::operator+=(const char *s)
{
    *this = *this + s;
}

void Str::operator+=(const char c)
{
    *this = *this + c;
}

Str &Str::append(const Str &obj)
{
    *this += obj;

    return *this;
}

Str &Str::append(const Str &obj, size_t subpos, size_t sublen)
{
    Str appender;

    appender.size = sublen;

    appender.data = new char[appender.size + 1];
    
    for(size_t i = 0; i < sublen; i++)
        appender.data[i] = obj.data[i + subpos];

    appender.data[appender.size] = '\0';

    *this += appender;

    return *this;
}

Str &Str::append(const char *s)
{
    *this += s;

    return *this;
}

Str &Str::append(const char *s, size_t n)
{
    Str appender;

    appender.size = n;
    appender.data = new char[n + 1];

    for(size_t i = 0; i < n; i++)
        appender.data[i] = s[i];

    appender.data[n] = '\0';

    *this += appender;

    return *this;
}

Str &Str::append(size_t n, char c)
{
    Str appender;

    appender.size = n;

    appender.data = new char[n + 1];

    for(size_t i = 0; i < n; i++)
        appender.data[i] = c;

    appender.data[n] = '\0';

    *this += appender;

    return *this;
}

void Str::push_back(char c)
{
    *this += c;
}

bool Str::operator==(const Str &obj)
{
    bool isEqual = false;

    if(this->size != obj.size)
        return isEqual;

    for(size_t i = 0; i < size; i++)
    {
        if(this->data[i] == obj.data[i])
            isEqual = true;

        else
        {
            isEqual = false;
            return isEqual;
        }
    }

    return isEqual;
}

bool Str::operator==(const char *s)
{
    bool isEqual = false;

    if(this->size != lengthOfCstr(s))
        return isEqual;

    for(size_t i = 0; i < size; i++)
    {
        if(this->data[i] == s[i])
            isEqual = true;

        else
        {
            isEqual = false;
            return isEqual;
        }
    }

    return isEqual;
}

bool Str::operator!=(const Str &obj)
{
    return !(*this == obj);
}

bool Str::operator!=(const char *s)
{
    return !(*this == s);
}

bool Str::operator<(const Str &obj)
{
    size_t controlSize;

    if(this->size > obj.size)
        controlSize = size;

    else
        controlSize = obj.size;

    for(size_t i = 0; i < controlSize; i++)
    {
        if(this->data[i] < obj.data[i])
            return true;

        else if(this->data[i] > obj.data[i])
            return false;
    }

    return false;
}

bool Str::operator<(const char *s)
{
    size_t controlSize;

    if(this->size > lengthOfCstr(s))
        controlSize = size;

    else
        controlSize = lengthOfCstr(s);

    for(size_t i = 0; i < controlSize; i++)
    {
        if(this->data[i] < s[i])
            return true;

        else if(this->data[i] > s[i])
            return false;
    }

    return false;
}

bool Str::operator>(const Str &obj)
{
    if(*this == obj)
        return false;
    
    return !(*this < obj);
}

bool Str::operator>(const char *s)
{
    if(*this == s)
        return false;

    return !(*this < s);
}

bool Str::operator<=(const Str &obj)
{
    return (*this < obj || *this == obj);
}

bool Str::operator<=(const char *s)
{
    return (*this < s || *this == s);
}

bool Str::operator>=(const Str &obj)
{
    return (*this > obj || *this == obj);
}

bool Str::operator>=(const char *s)
{
    return (*this > s || *this == s);
}

const char Str::operator[](size_t index)
{
    if(index >= size)
        throw std::out_of_range("Out of range!");

    return data[index];
}

const char Str::at(size_t index)
{
    return (*this)[index];
}

char &Str::back()
{
    return data[size - 1];
}

char &Str::front()
{
    return data[0];
}

StrIterator Str::begin()
{
    return data;
}

StrIterator Str::end()
{
    return data + size;
}

Str Str::substr(size_t index, size_t length)
{
    if (index >= size || index + length > size)
        throw std::out_of_range("Out of Range!");

    Str subString;

    subString.size = length;

    subString.data = new char[length + 1];

    for(size_t i = 0; i < length; i++)
        subString.data[i] = data[i + index];

    subString.data[length] = '\0';

    return subString;
}

size_t Str::find(const char *s, size_t index)
{
    for(size_t i = index; i < this->size; i++)
    {
        if(this->data[i] == s[0])
        {
            bool found = false;

            for(size_t j = 0; j < lengthOfCstr(s); j++)
            {
                if(this->data[i + j] == s[j])
                    found = true;

                else
                {
                    found = false;
                    break;
                }
            }

            if(found)
                return i;
        }
    }

    return Str::npos;
}

size_t Str::find(const Str &obj, size_t index)
{
    for(size_t i = index; i < this->size; i++)
    {
        if(this->data[i] == obj.data[0])
        {
            bool found = false;

            for(size_t j = 0; j < obj.size; j++)
            {
                if(this->data[i + j] == obj.data[j])
                    found = true;

                else
                    found = false;
            }

            if(found)
                return i;
        }
    }

    return Str::npos;
}

Str Str::erase(size_t index, size_t length)
{
    if (index >= size || index + length > size)
        throw std::out_of_range("Out of Range!");
    
    Str ans;

    ans.size = this->size - length;
    ans.data = new char[ans.size + 1];

    for (size_t i = 0; i < index; i++)
        ans.data[i] = this->data[i];

    for(size_t i = index; i < ans.size; i++)
        ans.data[i] = this->data[i + length];

    ans.data[ans.size] = '\0';

    return ans;
}

Str &Str::clear()
{
    delete[] this->data;
    this->data = nullptr;
    this->size = 0;

    return *this;
}

bool Str::empty()
{
    if(this->size == 0)
        return true;

    return false;
}

size_t Str::length()
{
    return size;
}

std::ostream &operator<<(std::ostream& os, const Str &obj)
{
    os << obj.data;

    return os;
}

std::istream &operator>>(std::istream &is, Str &obj)
{
    delete[] obj.data;
    obj.size = 0;

    size_t capacity = 16;
    char* temp = new char[capacity];

    char c;

    while(is.get(c) && !std::isspace(c))
    {
        if(obj.size + 1 == capacity)
        {
            capacity *= 2;
            char* newTemp = new char[capacity];

            for(size_t i = 0; i < obj.size; i++)
                newTemp[i] = temp[i];

            delete[] temp;
            temp = newTemp;
        }

        temp[obj.size++] = c;
    }

    obj.data = new char[obj.size + 1];
    for (size_t i = 0; i < obj.size; i++)
        obj.data[i] = temp[i];

    obj.data[obj.size] = '\0';

    delete[] temp;

    return is;
}

std::istream &s_getline(std::istream &is, Str &obj, char delimiter)
{
    delete[] obj.data;
    obj.size = 0;

    size_t capacity = 16;
    char* temp = new char[capacity];

    char c;

    while(is.get(c) && c != delimiter)
    {
        if(obj.size + 1 == capacity)
        {
            capacity *= 2;
            char* newTemp = new char[capacity];

            for(size_t i = 0; i < obj.size; i++)
                newTemp[i] = temp[i];

            delete[] temp;
            temp = newTemp;
        }

        temp[obj.size++] = c;
    }

    obj.data = new char[obj.size + 1];
    for (size_t i = 0; i < obj.size; i++)
        obj.data[i] = temp[i];

    obj.data[obj.size] = '\0';

    delete[] temp;

    return is;
}

size_t lengthOfCstr(const char *s)
{
    const char* ptr = s;
    size_t size = 0;

    while(*ptr != '\0')
    {
        size++;
        ptr++;
    }

    return size;
}
