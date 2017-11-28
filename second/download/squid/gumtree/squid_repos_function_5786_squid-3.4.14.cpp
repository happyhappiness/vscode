void
IpcIoFile::DiskerHandleMoreRequests(void *source)
{
    debugs(47, 7, HERE << "resuming handling requests after " <<
           static_cast<const char *>(source));
    DiskerHandleMoreRequestsScheduled = false;
    IpcIoFile::DiskerHandleRequests();
}