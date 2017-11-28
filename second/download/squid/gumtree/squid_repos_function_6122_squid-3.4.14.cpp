bool
ESIAssign::addElement(ESIElement::Pointer anElement)
{
    /* we have a value, drop the element on the floor */

    if (unevaluatedVariable.size())
        return true;

    if (!variable.getRaw())
        variable = new esiSequence (this, false);

    return variable->addElement (anElement);
}