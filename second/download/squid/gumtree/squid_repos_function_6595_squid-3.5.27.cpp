ESIElement::Pointer
esiWhen::makeUsable(esiTreeParentPtr newParent, ESIVarState &newVarState) const
{
    esiWhen *resultW = new esiWhen (*this);
    ESIElement::Pointer result = resultW;
    resultW->parent = newParent;
    resultW->makeUsableElements(*this, newVarState);
    resultW->varState = cbdataReference (&newVarState);
    resultW->evaluate();
    return result;
}