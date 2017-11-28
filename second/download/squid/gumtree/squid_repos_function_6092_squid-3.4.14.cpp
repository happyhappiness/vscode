void
ESISegment::ListTransfer (ESISegment::Pointer &from, ESISegment::Pointer &to)
{
    if (!to.getRaw()) {
        to = from;
        from = NULL;
        return;
    }

    ESISegment::Pointer temp = to->tail();
    temp->adsorbList (from);
    from = NULL;
}