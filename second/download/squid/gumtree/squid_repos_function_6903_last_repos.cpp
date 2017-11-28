void
ESIInclude::prepareRequestHeaders(HttpHeader &tempheaders, ESIVarState *vars)
{
    tempheaders.update(&vars->header());
    tempheaders.removeHopByHopEntries();
}