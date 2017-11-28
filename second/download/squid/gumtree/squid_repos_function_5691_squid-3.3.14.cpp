static void
diskerWrite(IpcIoMsg &ipcIo)
{
    const char *const buf = Ipc::Mem::PagePointer(ipcIo.page);
    const ssize_t wrote = pwrite(TheFile, buf, min(ipcIo.len, Ipc::Mem::PageSize()), ipcIo.offset);
    ++statCounter.syscalls.disk.writes;
    fd_bytes(TheFile, wrote, FD_WRITE);

    if (wrote >= 0) {
        ipcIo.xerrno = 0;
        const size_t len = static_cast<size_t>(wrote); // safe because wrote > 0
        debugs(47,8, HERE << "disker" << KidIdentifier << " wrote " <<
               (len == ipcIo.len ? "all " : "just ") << wrote);
        ipcIo.len = len;
    } else {
        ipcIo.xerrno = errno;
        ipcIo.len = 0;
        debugs(47,5, HERE << "disker" << KidIdentifier << " write error: " <<
               ipcIo.xerrno);
    }

    Ipc::Mem::PutPage(ipcIo.page);
}