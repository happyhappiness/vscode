ESIElement::Pointer
esiTry::makeUsable(esiTreeParentPtr newParent, ESIVarState &newVarState) const
{
    debugs(86, 5, "esiTry::makeUsable: making usable Try from " << this);
    esiTry *resultT = new esiTry (*this);
    ESIElement::Pointer result = resultT;

    resultT->parent = newParent;

    if (attempt.getRaw())
        resultT->attempt = attempt->makeUsable(resultT, newVarState);

    if (except.getRaw())
        resultT->except  = except->makeUsable(resultT, newVarState);

    return result;
}