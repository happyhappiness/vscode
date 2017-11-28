ESIAssign::Pointer
ESIAssign::makeUsable(esiTreeParentPtr aParent, ESIVarState &aVarState) const
{
    ESIAssign *result = new ESIAssign (*this);
    result->parent = aParent;
    result->varState = cbdataReference(&aVarState);

    if (variable.getRaw())
        result->variable = variable->makeUsable(result, aVarState);

    return result;
}