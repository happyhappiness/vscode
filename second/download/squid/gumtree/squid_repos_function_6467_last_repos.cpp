void
IpcIoFile::OpenTimeout(void *const param)
{
    Must(param);
    // the pointer is used for comparison only and not dereferenced
    const IpcIoFile *const ipcIoFile =
        reinterpret_cast<const IpcIoFile *>(param);
    for (IpcIoFileList::iterator i = WaitingForOpen.begin();
            i != WaitingForOpen.end(); ++i) {
        if (*i == ipcIoFile) {
            (*i)->openCompleted(NULL);
            WaitingForOpen.erase(i);
            break;
        }
    }
}