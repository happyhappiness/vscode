void
Fs::Ufs::UFSStoreState::drainWriteQueue()
{
    /*
     * DPW 2007-04-12
     * We might find that flags.write_draining is already set
     * because schemes like diskd can process I/O acks
     * before sending another I/O request.    e.g. the following
     * sequence of events: open request -> write request ->
     * drainWriteQueue() -> queue full -> callbacks -> openDone() ->
     * drainWriteQueue().
     */
    if (flags.write_draining)
        return;

    if (!theFile || !theFile->canWrite())
        return;

    flags.write_draining = true;

    while (!pending_writes.empty())
        doWrite();

    flags.write_draining = false;

    if (flags.try_closing)
        tryClosing();
}