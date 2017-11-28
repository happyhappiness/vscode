void
IdleConnList::push(const Comm::ConnectionPointer &conn)
{
    if (size_ == capacity_) {
        debugs(48, 3, HERE << "growing idle Connection array");
        capacity_ <<= 1;
        const Comm::ConnectionPointer *oldList = theList_;
        theList_ = new Comm::ConnectionPointer[capacity_];
        for (int index = 0; index < size_; ++index)
            theList_[index] = oldList[index];

        delete[] oldList;
    }

    if (parent_)
        parent_->noteConnectionAdded();

    theList_[size_] = conn;
    ++size_;
    AsyncCall::Pointer readCall = commCbCall(5,4, "IdleConnList::Read",
                                  CommIoCbPtrFun(IdleConnList::Read, this));
    comm_read(conn, fakeReadBuf_, sizeof(fakeReadBuf_), readCall);
    AsyncCall::Pointer timeoutCall = commCbCall(5,4, "IdleConnList::Timeout",
                                     CommTimeoutCbPtrFun(IdleConnList::Timeout, this));
    commSetConnTimeout(conn, conn->timeLeft(Config.Timeout.serverIdlePconn), timeoutCall);
}