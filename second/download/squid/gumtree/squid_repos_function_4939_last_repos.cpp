bool
Rock::SwapDir::needsDiskStrand() const
{
    const bool wontEvenWorkWithoutDisker = Config.workers > 1;
    const bool wouldWorkBetterWithDisker = DiskIOModule::Find("IpcIo");
    return InDaemonMode() && (wontEvenWorkWithoutDisker ||
                              wouldWorkBetterWithDisker);
}