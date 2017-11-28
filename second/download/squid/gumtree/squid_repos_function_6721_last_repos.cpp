void
ESIContext::freeResources ()
{
    debugs(86, 5, HERE << "Freeing for this=" << this);

    rep = nullptr; // refcounted

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