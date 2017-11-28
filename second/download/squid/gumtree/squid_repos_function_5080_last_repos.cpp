void
Fs::Ufs::UFSStoreState::writeCompleted(int, size_t len, RefCount<WriteRequest>)
{
    debugs(79, 3, HERE << "dirno " << swap_dirn << ", fileno " <<
           std::setfill('0') << std::hex << std::uppercase << std::setw(8) << swap_filen <<
           ", len " << len);
    /*
     * DPW 2006-05-24
     * See doWrites() for why we don't update UFSStoreState::writing
     * here anymore.
     */

    offset_ += len;

    if (theFile->error()) {
        debugs(79,2,HERE << " detected an error, will try to close");
        tryClosing();
    }

    /*
     * HNO 2009-07-24
     * Kick any pending write/close operations alive
     */
    drainWriteQueue();
}