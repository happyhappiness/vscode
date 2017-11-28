void
ESIInclude::prepareRequestHeaders(HttpHeader &tempheaders, ESIVarState *vars)
{
    tempheaders.update (&vars->header(), NULL);
    tempheaders.removeHopByHopEntries();
}