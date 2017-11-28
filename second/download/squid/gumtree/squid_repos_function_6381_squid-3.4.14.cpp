void
Ipc::FewToFewBiQueue::clearReaderSignal(const int remoteProcessId)
{
    QueueReader &localReader = reader(theLocalGroup, theLocalProcessId);
    debugs(54, 7, HERE << "reader: " << localReader.id);

    Must(validProcessId(remoteGroup(), remoteProcessId));
    localReader.clearSignal();

    // we got a hint; we could reposition iteration to try popping from the
    // remoteProcessId queue first; but it does not seem to help much and might
    // introduce some bias so we do not do that for now:
    // theLastPopProcessId = remoteProcessId;
}