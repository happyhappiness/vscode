void
esiVarStateFree (void *data)
{
    ESIVarState *thisNode = (ESIVarState*)data;
    thisNode->freeResources();
}