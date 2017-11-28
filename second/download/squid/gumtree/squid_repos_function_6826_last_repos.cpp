void
ESIVarState::feedData (const char *buf, size_t len)
{
    /* TODO: if needed - tune to skip segment iteration */
    debugs (86,6, "esiVarState::feedData: accepting " << len << " bytes");
    ESISegment::ListAppend (input, buf, len);
}