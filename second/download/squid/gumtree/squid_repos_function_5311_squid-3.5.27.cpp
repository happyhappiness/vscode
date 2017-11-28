bool
Fs::Ufs::UFSSwapDir::unlinkdUseful() const
{
    // unlinkd may be useful only in workers
    return IamWorkerProcess() && IO->io->unlinkdUseful();
}