bool operator == (ESIElement const *lhs, ESIElement::Pointer const &rhs)
{
    return lhs == rhs.getRaw();
}