void
IpcIoFile::CheckTimeouts(void *const param)
{
    Must(param);
    const int diskId = reinterpret_cast<uintptr_t>(param);
    debugs(47, 7, HERE << "diskId=" << diskId);
    const IpcIoFilesMap::const_iterator i = IpcIoFiles.find(diskId);
    if (i != IpcIoFiles.end())
        i->second->checkTimeouts();
}