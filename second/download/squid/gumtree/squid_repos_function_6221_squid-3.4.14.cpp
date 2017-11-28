ESIElement::Pointer
ESIInclude::makeCacheable() const
{
    return new ESIInclude (*this);
}