void
ESIVarState::freeResources()
{
    input = NULL;
    ESISegmentFreeList (output);
    hdr.clean();
}