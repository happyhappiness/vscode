void
esiChoose::checkValidSource (ESIElement::Pointer source) const
{
    if (!elements.size())
        fatal ("invalid callback = no when clause\n");

    if (chosenelement >= 0)
        assert (source == elements[chosenelement]);
    else if (otherwise.getRaw())
        assert (source == otherwise);
    else
        fatal ("esiChoose::checkValidSource: invalid callback - no elements chosen\n");
}