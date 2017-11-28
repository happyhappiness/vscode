ESIElement::Pointer
esiChoose::makeUsable(esiTreeParentPtr newParent, ESIVarState &newVarState) const
{
    esiChoose *resultC = new esiChoose (*this);
    ESIElement::Pointer result = resultC;
    resultC->parent = newParent;
    resultC->makeUsableElements(*this, newVarState);
    resultC->selectElement();

    if (otherwise.getRaw())
        resultC->otherwise = otherwise->makeUsable(resultC, newVarState);

    return result;
}