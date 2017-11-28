void
ElementList::push_back(ESIElement::Pointer &newElement)
{
    elements = (ESIElement::Pointer *)memReallocBuf (elements, ++elementcount * sizeof (ESIElement::Pointer),
               &allocedsize);
    assert (elements);
    allocedcount = elementcount;
    memset(&elements[elementcount - 1], '\0', sizeof (ESIElement::Pointer));
    elements[elementcount - 1] = newElement;
}