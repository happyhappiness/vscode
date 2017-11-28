void
Rock::HeaderUpdater::stopReading(const char *why)
{
    debugs(47, 7, why);

    Must(reader);
    const IoState &rockReader = dynamic_cast<IoState&>(*reader);
    update.stale.splicingPoint = rockReader.splicingPoint;
    staleSplicingPointNext = rockReader.staleSplicingPointNext;
    debugs(47, 5, "stale chain ends at " << update.stale.splicingPoint <<
           " body continues at " << staleSplicingPointNext);

    reader->close(StoreIOState::readerDone); // calls noteDoneReading(0)
    reader = nullptr; // so that swanSong() does not try to close again
}