void
esiChoose::makeCachableElements(esiChoose const &old)
{
    for (size_t counter = 0; counter < old.elements.size(); ++counter) {
        ESIElement::Pointer newElement = old.elements[counter]->makeCacheable();

        if (newElement.getRaw())
            assert (addElement(newElement));
    }
}