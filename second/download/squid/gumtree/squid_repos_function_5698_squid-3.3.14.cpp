void
IpcIoClaimMemoryNeedsRr::run(const RunnerRegistry &)
{
    const int itemsCount = Ipc::FewToFewBiQueue::MaxItemsCount(
                               ::Config.workers, ::Config.cacheSwap.n_strands, QueueCapacity);
    // the maximum number of shared I/O pages is approximately the
    // number of queue slots, we add a fudge factor to that to account
    // for corner cases where I/O pages are created before queue
    // limits are checked or destroyed long after the I/O is dequeued
    Ipc::Mem::NotePageNeed(Ipc::Mem::PageId::ioPage,
                           static_cast<int>(itemsCount * 1.1));
}