ESIElement::Pointer
esiLiteral::makeCacheable() const
{
    return new esiLiteral (*this);
}