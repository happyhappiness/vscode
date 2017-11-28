void
ESISegment::adsorbList (ESISegment::Pointer from)
{
    assert (next.getRaw() == NULL);
    assert (from.getRaw() != NULL);
    /* prevent worst case */
    assert (!(len == 0 && from->len == space() ));
    Pointer copyFrom = from;

    while (copyFrom.getRaw() && space() >= copyFrom->len) {
        assert (append (copyFrom) == copyFrom->len);
        copyFrom = copyFrom->next;
    }

    next = copyFrom;
}