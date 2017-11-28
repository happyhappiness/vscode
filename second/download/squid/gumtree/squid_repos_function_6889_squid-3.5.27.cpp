void
Ipc::BaseMultiQueue::clearReaderSignal(const int remoteProcessId)
{
    QueueReader &reader = localReader();
    debugs(54, 7, "reader: " << reader.id);

    reader.clearSignal();

    // we got a hint; we could reposition iteration to try popping from the
    // remoteProcessId queue first; but it does not seem to help much and might
    // introduce some bias so we do not do that for now:
    // theLastPopProcessId = remoteProcessId;
}