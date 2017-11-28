void
esiChoose::makeUsableElements(esiChoose const &old, ESIVarState &newVarState)
{
    for (size_t counter = 0; counter < old.elements.size(); ++counter) {
        ESIElement::Pointer newElement = old.elements[counter]->makeUsable (this, newVarState);

        if (newElement.getRaw())
            assert (addElement(newElement));
    }
}