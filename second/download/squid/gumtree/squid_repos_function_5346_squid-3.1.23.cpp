void
ESIContext::freeResources ()
{
    debugs(86, 5, HERE << "Freeing for this=" << this);

    HTTPMSGUNLOCK(rep);

    finishChildren ();

    if (parserState.inited()) {
        parserState.freeResources();
    }

    parserState.popAll();
    ESISegmentFreeList (buffered);
    ESISegmentFreeList (outbound);
    ESISegmentFreeList (outboundtail);
    delete varState;
    varState=NULL;
    /* don't touch incoming, it's a pointer into buffered anyway */
}