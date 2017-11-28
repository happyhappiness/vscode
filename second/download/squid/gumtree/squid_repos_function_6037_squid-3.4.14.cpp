void
esiLiteral::render (ESISegment::Pointer output)
{
    debugs(86, 9, "esiLiteral::render: Rendering " << this);
    /* append the entire chain */
    assert (output->next.getRaw() == NULL);
    output->next = buffer;
    buffer = NULL;
}