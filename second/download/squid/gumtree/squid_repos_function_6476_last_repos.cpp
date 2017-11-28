static void
diskerWrite(IpcIoMsg &ipcIo)
{
    diskerWriteAttempts(ipcIo); // may fail
    Ipc::Mem::PutPage(ipcIo.page);
}