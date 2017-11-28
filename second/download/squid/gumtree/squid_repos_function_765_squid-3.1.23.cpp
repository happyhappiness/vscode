void
ClientHttpRequest::loggingEntry(StoreEntry *newEntry)
{
    if (loggingEntry_)
        loggingEntry_->unlock();

    loggingEntry_ = newEntry;

    if (loggingEntry_)
        loggingEntry_->lock();
}