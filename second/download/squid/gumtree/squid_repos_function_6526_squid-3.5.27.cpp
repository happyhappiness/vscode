void
esiStreamDetach (clientStreamNode *thisNode, ClientHttpRequest *http)
{
    /* if we have pending callbacks, tell them we're done. */
    /* test preconditions */
    assert (thisNode != NULL);
    assert (cbdataReferenceValid (thisNode));
    ESIContext::Pointer context = dynamic_cast<ESIContext *>(thisNode->data.getRaw());
    assert (context.getRaw() != NULL);
    /* detach from the stream */
    clientStreamDetach (thisNode,http);
    /* if we have pending callbacks (from subincludes), tell them we're done. */
    context->thisNode = NULL;
    context->flags.detached = 1;
    context->finishChildren();
    /* HACK for parser stack not being emptied */
    context->parserState.stack[0] = NULL;
    /* allow refcount logic to trigger */
    context->cbdataLocker = NULL;
}