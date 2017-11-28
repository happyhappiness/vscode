CharacterSet
CharacterSet::operator +(const CharacterSet &src) const
{
    CharacterSet rv(*this);
    rv += src;
    return rv;
}