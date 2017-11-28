void
ElementList::pop_front (size_t const count)
{
    if (!count)
        return;

    xmemmove (elements, &elements[count], (elementcount - count)  * sizeof (ESIElement::Pointer));

    elementcount -= count;
}