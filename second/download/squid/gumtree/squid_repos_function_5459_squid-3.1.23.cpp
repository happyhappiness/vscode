ESISegment::Pointer
ESIVarState::extractList()
{
    doIt();
    ESISegment::Pointer rv = output;
    output = NULL;
    debugs(86, 6, "ESIVarStateExtractList: Extracted list");
    return rv;
}