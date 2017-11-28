ESIElement::Pointer
esiLiteral::makeUsable(esiTreeParentPtr , ESIVarState &newVarState) const
{
    debugs(86, 5, "esiLiteral::makeUsable: Creating usable literal");
    esiLiteral * result = new esiLiteral (*this);
    result->varState = cbdataReference (&newVarState);
    return result;
}