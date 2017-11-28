bool
IpcIoFile::WaitBeforePop()
{
    const Ipc::QueueReader::Rate::Value ioRate = queue->localRateLimit();
    const double maxRate = ioRate/1e3; // req/ms

    // do we need to enforce configured I/O rate?
    if (maxRate <= 0)
        return false;

    // is there an I/O request we could potentially delay?
    int processId;
    IpcIoMsg ipcIo;
    if (!queue->peek(processId, ipcIo)) {
        // unlike pop(), peek() is not reliable and does not block reader
        // so we must proceed with pop() even if it is likely to fail
        return false;
    }

    static timeval LastIo = current_time;

    const double ioDuration = 1.0 / maxRate; // ideal distance between two I/Os
    // do not accumulate more than 100ms or 100 I/Os, whichever is smaller
    const int64_t maxImbalance = min(static_cast<int64_t>(100), static_cast<int64_t>(100 * ioDuration));

    const double credit = ioDuration; // what the last I/O should have cost us
    const double debit = tvSubMsec(LastIo, current_time); // actual distance from the last I/O
    LastIo = current_time;

    Ipc::QueueReader::Balance &balance = queue->localBalance();
    balance += static_cast<int64_t>(credit - debit);

    debugs(47, 7, HERE << "rate limiting balance: " << balance << " after +" << credit << " -" << debit);

    if (ipcIo.command == IpcIo::cmdWrite && balance > maxImbalance) {
        // if the next request is (likely) write and we accumulated
        // too much time for future slow I/Os, then shed accumulated
        // time to keep just half of the excess
        const int64_t toSpend = balance - maxImbalance/2;

        if (toSpend/1e3 > Timeout)
            debugs(47, DBG_IMPORTANT, "WARNING: " << DbName << " delays " <<
                   "I/O requests for " << (toSpend/1e3) << " seconds " <<
                   "to obey " << ioRate << "/sec rate limit");

        debugs(47, 3, HERE << "rate limiting by " << toSpend << " ms to get" <<
               (1e3*maxRate) << "/sec rate");
        eventAdd("IpcIoFile::DiskerHandleMoreRequests",
                 &IpcIoFile::DiskerHandleMoreRequests,
                 const_cast<char*>("rate limiting"),
                 toSpend/1e3, 0, false);
        DiskerHandleMoreRequestsScheduled = true;
        return true;
    } else if (balance < -maxImbalance) {
        // do not owe "too much" to avoid "too large" bursts of I/O
        balance = -maxImbalance;
    }

    return false;
}