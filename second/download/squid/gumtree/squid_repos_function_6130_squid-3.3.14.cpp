void
ESIStreamContext::freeResources()
{
    debugs(86, 5, "Freeing stream context resources.");
    buffer = NULL;
    localbuffer = NULL;
    include = NULL;
}