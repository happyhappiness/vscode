void
IpcIoFile::DiskerHandleRequests()
{
    // Balance our desire to maximize the number of concurrent I/O requests
    // (reordred by OS to minimize seek time) with a requirement to
    // send 1st-I/O notification messages, process Coordinator events, etc.
    const int maxSpentMsec = 10; // keep small: most RAM I/Os are under 1ms
    const timeval loopStart = current_time;

    int popped = 0;
    int workerId = 0;
    IpcIoMsg ipcIo;
    while (!WaitBeforePop() && queue->pop(workerId, ipcIo)) {
        ++popped;

        // at least one I/O per call is guaranteed if the queue is not empty
        DiskerHandleRequest(workerId, ipcIo);

        getCurrentTime();
        const double elapsedMsec = tvSubMsec(loopStart, current_time);
        if (elapsedMsec > maxSpentMsec || elapsedMsec < 0) {
            if (!DiskerHandleMoreRequestsScheduled) {
                // the gap must be positive for select(2) to be given a chance
                const double minBreakSecs = 0.001;
                eventAdd("IpcIoFile::DiskerHandleMoreRequests",
                         &IpcIoFile::DiskerHandleMoreRequests,
                         const_cast<char*>("long I/O loop"),
                         minBreakSecs, 0, false);
                DiskerHandleMoreRequestsScheduled = true;
            }
            debugs(47, 3, HERE << "pausing after " << popped << " I/Os in " <<
                   elapsedMsec << "ms; " << (elapsedMsec/popped) << "ms per I/O");
            break;
        }
    }

    // TODO: consider using O_DIRECT with "elevator" optimization where we pop
    // requests first, then reorder the popped requests to optimize seek time,
    // then do I/O, then take a break, and come back for the next set of I/O
    // requests.
}