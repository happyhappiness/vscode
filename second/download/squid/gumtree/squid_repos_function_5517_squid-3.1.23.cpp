int
esiSequence::elementIndex(ESIElement::Pointer anElement) const
{
    for (size_t i = 0; i < elements.size(); ++i)
        if (elements[i] == anElement)
            return i;

    return -1;
}