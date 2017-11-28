std::ostream&
operator <<(std::ostream &s, const CharacterSet &c)
{
    s << "CharacterSet(" << c.name << ')';
    return s;
}