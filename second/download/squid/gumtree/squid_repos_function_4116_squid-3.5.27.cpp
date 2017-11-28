void Adaptation::Icap::ModXact::addLastRequestChunk(MemBuf &buf)
{
    const bool ieof = state.writing == State::writingPreview && preview.ieof();
    openChunk(buf, 0, ieof);
    closeChunk(buf);
}