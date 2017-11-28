void
SBufStatsAction::collect()
{
    sbdata = SBuf::GetStats();
    mbdata = MemBlob::GetStats();
    sbsizesatdestruct = collectSBufDestructTimeStats();
    mbsizesatdestruct = collectMemBlobDestructTimeStats();
}