void
IpcIoFile::HandleOpenResponse(const Ipc::StrandSearchResponse &response)
{
    debugs(47, 7, HERE << "coordinator response to open request");
    for (IpcIoFileList::iterator i = WaitingForOpen.begin();
            i != WaitingForOpen.end(); ++i) {
        if (response.strand.tag == (*i)->dbName) {
            (*i)->openCompleted(&response);
            WaitingForOpen.erase(i);
            return;
        }
    }

    debugs(47, 4, HERE << "LATE disker response to open for " <<
           response.strand.tag);
    // nothing we can do about it; completeIo() has been called already
}