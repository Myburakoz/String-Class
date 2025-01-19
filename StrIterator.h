class StrIterator
{
    char* iterator;

    public:
    StrIterator(char* ptr);
    char& operator*();
    StrIterator& operator++();
    bool operator!=(const StrIterator& obj);

    friend std::ostream& operator<<(std::ostream& os, const StrIterator& obj);
};

StrIterator::StrIterator(char* ptr)
{
    iterator = ptr;
}

char &StrIterator::operator*()
{
    return *iterator;
}

StrIterator &StrIterator::operator++()
{
    ++iterator;
    return *this;
}

bool StrIterator::operator!=(const StrIterator &obj)
{
    return iterator != obj.iterator;
}

std::ostream& operator<<(std::ostream& os, const StrIterator& obj)
{
    os << obj.iterator[0];

    return os;
}
