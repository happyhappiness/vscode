static void
diskerWriteAttempts(IpcIoMsg &ipcIo)
{
    const char *buf = Ipc::Mem::PagePointer(ipcIo.page);
    size_t toWrite = min(ipcIo.len, Ipc::Mem::PageSize());
    size_t wroteSoFar = 0;
    off_t offset = ipcIo.offset;
    // Partial writes to disk do happen. It is unlikely that the caller can
    // handle partial writes by doing something other than writing leftovers
    // again, so we try to write them ourselves to minimize overheads.
    const int attemptLimit = 10;
    for (int attempts = 1; attempts <= attemptLimit; ++attempts) {
        const ssize_t result = pwrite(TheFile, buf, toWrite, offset);
        ++statCounter.syscalls.disk.writes;
        fd_bytes(TheFile, result, FD_WRITE);

        if (result < 0) {
            ipcIo.xerrno = errno;
            assert(ipcIo.xerrno);
            debugs(47, DBG_IMPORTANT, "ERROR: " << DbName << " failure" <<
                   " writing " << toWrite << '/' << ipcIo.len <<
                   " at " << ipcIo.offset << '+' << wroteSoFar <<
                   " on " << attempts << " try: " << xstrerr(ipcIo.xerrno));
            ipcIo.len = wroteSoFar;
            return; // bail on error
        }

        const size_t wroteNow = static_cast<size_t>(result); // result >= 0
        ipcIo.xerrno = 0;

        debugs(47,3, "disker" << KidIdentifier << " wrote " <<
               (wroteNow >= toWrite ? "all " : "just ") << wroteNow <<
               " out of " << toWrite << '/' << ipcIo.len << " at " <<
               ipcIo.offset << '+' << wroteSoFar << " on " << attempts <<
               " try");

        wroteSoFar += wroteNow;

        if (wroteNow >= toWrite) {
            ipcIo.xerrno = 0;
            ipcIo.len = wroteSoFar;
            return; // wrote everything there was to write
        }

        buf += wroteNow;
        offset += wroteNow;
        toWrite -= wroteNow;
    }

    debugs(47, DBG_IMPORTANT, "ERROR: " << DbName << " exhausted all " <<
           attemptLimit << " attempts while writing " <<
           toWrite << '/' << ipcIo.len << " at " << ipcIo.offset << '+' <<
           wroteSoFar);
    return; // not a fatal I/O error, unless the caller treats it as such
}