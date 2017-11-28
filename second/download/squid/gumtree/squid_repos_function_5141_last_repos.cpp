void
Fs::Ufs::UFSSwapDir::CleanEvent(void *)
{
    const int n = HandleCleanEvent();
    eventAdd("storeDirClean", CleanEvent, NULL,
             15.0 * exp(-0.25 * n), 1);
}