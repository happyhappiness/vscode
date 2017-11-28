bool
IpcIoFile::canWait() const
{
    if (!config.ioTimeout)
        return true; // no timeout specified

    IpcIoMsg oldestIo;
    if (!queue->findOldest(diskId, oldestIo) || oldestIo.start.tv_sec <= 0)
        return true; // we cannot estimate expected wait time; assume it is OK

    const int oldestWait = tvSubMsec(oldestIo.start, current_time);

    int rateWait = -1; // time in millisecons
    const Ipc::QueueReader::Rate::Value ioRate = queue->rateLimit(diskId);
    if (ioRate > 0) {
        // if there are N requests pending, the new one will wait at
        // least N/max-swap-rate seconds
        rateWait = static_cast<int>(1e3 * queue->outSize(diskId) / ioRate);
        // adjust N/max-swap-rate value based on the queue "balance"
        // member, in case we have been borrowing time against future
        // I/O already
        rateWait += queue->balance(diskId);
    }

    const int expectedWait = max(oldestWait, rateWait);
    if (expectedWait < 0 ||
            static_cast<time_msec_t>(expectedWait) < config.ioTimeout)
        return true; // expected wait time is acceptible

    debugs(47,2, HERE << "cannot wait: " << expectedWait <<
           " oldest: " << SipcIo(KidIdentifier, oldestIo, diskId));
    return false; // do not want to wait that long
}