void
Comm::AcceptLimiter::kick()
{
    // TODO: this could be optimized further with an iterator to search
    //       looking for first non-NULL, followed by dumping the first N
    //       with only one shift()/pop_front operation
    //  OR, by reimplementing as a list instead of Vector.

    debugs(5, 5, "size=" << deferred_.size());
    while (deferred_.size() > 0 && fdNFree() >= RESERVED_FD) {
        /* NP: shift() is equivalent to pop_front(). Giving us a FIFO queue. */
        TcpAcceptor::Pointer temp = deferred_.front();
        deferred_.erase(deferred_.begin());
        if (temp.valid()) {
            debugs(5, 5, "doing one.");
            -- temp->isLimited;
            temp->acceptNext();
            break;
        }
    }
}