static void
diskerRead(IpcIoMsg &ipcIo)
{
    if (!Ipc::Mem::GetPage(Ipc::Mem::PageId::ioPage, ipcIo.page)) {
        ipcIo.len = 0;
        debugs(47,2, HERE << "run out of shared memory pages for IPC I/O");
        return;
    }

    char *const buf = Ipc::Mem::PagePointer(ipcIo.page);
    const ssize_t read = pread(TheFile, buf, min(ipcIo.len, Ipc::Mem::PageSize()), ipcIo.offset);
    ++statCounter.syscalls.disk.reads;
    fd_bytes(TheFile, read, FD_READ);

    if (read >= 0) {
        ipcIo.xerrno = 0;
        const size_t len = static_cast<size_t>(read); // safe because read > 0
        debugs(47,8, HERE << "disker" << KidIdentifier << " read " <<
               (len == ipcIo.len ? "all " : "just ") << read);
        ipcIo.len = len;
    } else {
        ipcIo.xerrno = errno;
        ipcIo.len = 0;
        debugs(47,5, HERE << "disker" << KidIdentifier << " read error: " <<
               ipcIo.xerrno);
    }
}