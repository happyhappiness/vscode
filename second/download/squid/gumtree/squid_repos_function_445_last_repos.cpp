void
ClientHttpRequest::loggingEntry(StoreEntry *newEntry)
{
    if (loggingEntry_)
        loggingEntry_->unlock("ClientHttpRequest::loggingEntry");

    loggingEntry_ = newEntry;

    if (loggingEntry_)
        loggingEntry_->lock("ClientHttpRequest::loggingEntry");
}