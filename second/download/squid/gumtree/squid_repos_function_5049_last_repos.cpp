void
Rock::HeaderUpdater::start()
{
    Must(update.entry);
    Must(update.stale);
    Must(update.fresh);
    startReading();
}