void
ESIContext::provideData (ESISegment::Pointer theData, ESIElement * source)
{
    debugs(86, 5, "ESIContext::provideData: " << this << " " << theData.getRaw() << " " << source);
    /* No callbacks permitted after finish() called on the tree */
    assert (tree.getRaw());
    assert (source == tree);
    appendOutboundData(theData);
    trimBlanks();

    if (!processing)
        send();
}