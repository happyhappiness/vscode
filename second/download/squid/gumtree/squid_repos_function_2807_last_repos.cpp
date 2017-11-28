void
IdleConnList::closeN(size_t n)
{
    if (n < 1) {
        debugs(48, 2, HERE << "Nothing to do.");
        return;
    } else if (n >= (size_t)size_) {
        debugs(48, 2, HERE << "Closing all entries.");
        while (size_ > 0) {
            const Comm::ConnectionPointer conn = theList_[--size_];
            theList_[size_] = NULL;
            clearHandlers(conn);
            conn->close();
            if (parent_)
                parent_->noteConnectionRemoved();
        }
    } else { //if (n < size_)
        debugs(48, 2, HERE << "Closing " << n << " of " << size_ << " entries.");

        size_t index;
        // ensure the first N entries are closed
        for (index = 0; index < n; ++index) {
            const Comm::ConnectionPointer conn = theList_[index];
            theList_[index] = NULL;
            clearHandlers(conn);
            conn->close();
            if (parent_)
                parent_->noteConnectionRemoved();
        }
        // shuffle the list N down.
        for (index = 0; index < (size_t)size_ - n; ++index) {
            theList_[index] = theList_[index + n];
        }
        // ensure the last N entries are unset
        while (index < ((size_t)size_)) {
            theList_[index] = NULL;
            ++index;
        }
        size_ -= n;
    }

    if (parent_ && size_ == 0) {
        debugs(48, 3, "deleting " << hashKeyStr(this));
        delete this;
    }
}