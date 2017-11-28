void
esiBufferDetach (clientStreamNode *node, ClientHttpRequest *http)
{
    /* Detach ourselves */
    clientStreamDetach (node, http);
}