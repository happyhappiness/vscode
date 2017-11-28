void
esiSequence::provideData (ESISegment::Pointer data, ESIElement *source)
{
    ESIElement::Pointer lockthis = this;

    if (processing)
        debugs(86, 5, "esiSequence::provideData: " << this << " data provided during processing");
    debugs(86, 5, "esiSequence::provideData " << this << " " << data.getRaw() << " " << source);

    /* when data is provided, the element *must* be completed */
    /* XXX: when the callback model is complete,
     * we can introduce 'finished'. And then this rule can be
     * relaxed
     */
    /* find the index */
    int index = elementIndex (source);

    assert (index >= 0);

    /* remove the current node */
    elements.setNULL(index, index+1);

    /* create a literal */
    esiLiteral *temp = new esiLiteral (data);

    /* insert the literal */
    elements[index] = temp;

    /* XXX: TODO push any pushable data upwards */
    /* fail() not done */
    if (processing)
        return;

    assert (process (flags.dovars) != ESI_PROCESS_FAILED);
}