CharacterSet &
CharacterSet::operator -=(const CharacterSet &src)
{
    Storage::const_iterator s = src.chars_.begin();
    const Storage::const_iterator e = src.chars_.end();
    Storage::iterator d = chars_.begin();
    while (s != e) {
        if (*s)
            *d = 0;
        ++s;
        ++d;
    }
    return *this;
}