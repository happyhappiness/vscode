void
IpcIoFile::HandleResponses(const char *const when)
{
    debugs(47, 4, HERE << "popping all " << when);
    IpcIoMsg ipcIo;
    // get all responses we can: since we are not pushing, this will stop
    int diskId;
    while (queue->pop(diskId, ipcIo)) {
        const IpcIoFilesMap::const_iterator i = IpcIoFiles.find(diskId);
        Must(i != IpcIoFiles.end()); // TODO: warn but continue
        i->second->handleResponse(ipcIo);
    }
}