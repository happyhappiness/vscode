ESIElement::Pointer
esiWhen::makeCacheable() const
{
    return new esiWhen(*this);
}