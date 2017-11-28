void
ClientInfo::kickQuotaQueue()
{
    if (!eventWaiting && !selectWaiting && hasQueue()) {
        // wait at least a second if the bucket is empty
        const double delay = (bucketSize < 1.0) ? 1.0 : 0.0;
        eventAdd("commHandleWriteHelper", &commHandleWriteHelper,
                 quotaQueue, delay, 0, true);
        eventWaiting = true;
    }
}