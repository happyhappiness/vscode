bool
Comm::ConnOpener::doneAll() const
{
    // is the conn_ to be opened still waiting?
    if (conn_ == NULL) {
        return AsyncJob::doneAll();
    }

    // is the callback still to be called?
    if (callback_ == NULL || callback_->canceled()) {
        return AsyncJob::doneAll();
    }

    // otherwise, we must be waiting for something
    Must(temporaryFd_ >= 0 || calls_.sleep_);
    return false;
}