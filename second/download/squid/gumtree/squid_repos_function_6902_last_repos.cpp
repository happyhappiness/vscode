ESIElement::Pointer
ESIInclude::makeUsable(esiTreeParentPtr newParent, ESIVarState &newVarState) const
{
    ESIInclude *resultI = new ESIInclude (*this);
    ESIElement::Pointer result = resultI;
    resultI->parent = newParent;
    resultI->varState = cbdataReference (&newVarState);

    if (resultI->srcurl)
        resultI->src = ESIStreamContextNew (resultI);

    if (resultI->alturl)
        resultI->alt = ESIStreamContextNew (resultI);

    return result;
}