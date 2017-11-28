void
SBufStatsAction::dump(StoreEntry* entry)
{
    StoreEntryStream ses(entry);
    ses << "\n\n\nThese statistics are experimental; their format and contents "
        "should not be relied upon, they are bound to change as "
        "the SBuf feature is evolved\n";
    sbdata.dump(ses);
    mbdata.dump(ses);
    ses << "\n";
    ses << "SBuf size distribution at destruct time:\n";
    sbsizesatdestruct.dump(entry,statHistSBufDumper);
    ses << "MemBlob capacity distribution at destruct time:\n";
    mbsizesatdestruct.dump(entry,statHistSBufDumper);
}