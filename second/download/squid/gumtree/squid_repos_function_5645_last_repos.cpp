void
Comm::HandleWrite(int fd, void *data)
{
    Comm::IoCallback *state = static_cast<Comm::IoCallback *>(data);
    int len = 0;
    int nleft;

    assert(state->conn != NULL && state->conn->fd == fd);

    PROF_start(commHandleWrite);
    debugs(5, 5, HERE << state->conn << ": off " <<
           (long int) state->offset << ", sz " << (long int) state->size << ".");

    nleft = state->size - state->offset;

#if USE_DELAY_POOLS
    ClientInfo * clientInfo=fd_table[fd].clientInfo;

    if (clientInfo && !clientInfo->writeLimitingActive)
        clientInfo = NULL; // we only care about quota limits here

    if (clientInfo) {
        assert(clientInfo->selectWaiting);
        clientInfo->selectWaiting = false;

        assert(clientInfo->hasQueue());
        assert(clientInfo->quotaPeekFd() == fd);
        clientInfo->quotaDequeue(); // we will write or requeue below

        if (nleft > 0) {
            const int quota = clientInfo->quotaForDequed();
            if (!quota) {  // if no write quota left, queue this fd
                state->quotaQueueReserv = clientInfo->quotaEnqueue(fd);
                clientInfo->kickQuotaQueue();
                PROF_stop(commHandleWrite);
                return;
            }

            const int nleft_corrected = min(nleft, quota);
            if (nleft != nleft_corrected) {
                debugs(5, 5, HERE << state->conn << " writes only " <<
                       nleft_corrected << " out of " << nleft);
                nleft = nleft_corrected;
            }

        }
    }
#endif /* USE_DELAY_POOLS */

    /* actually WRITE data */
    int xerrno = errno = 0;
    len = FD_WRITE_METHOD(fd, state->buf + state->offset, nleft);
    xerrno = errno;
    debugs(5, 5, HERE << "write() returns " << len);

#if USE_DELAY_POOLS
    if (clientInfo) {
        if (len > 0) {
            /* we wrote data - drain them from bucket */
            clientInfo->bucketSize -= len;
            if (clientInfo->bucketSize < 0.0) {
                debugs(5, DBG_IMPORTANT, HERE << "drained too much"); // should not happen
                clientInfo->bucketSize = 0;
            }
        }

        // even if we wrote nothing, we were served; give others a chance
        clientInfo->kickQuotaQueue();
    }
#endif /* USE_DELAY_POOLS */

    fd_bytes(fd, len, FD_WRITE);
    ++statCounter.syscalls.sock.writes;
    // After each successful partial write,
    // reset fde::writeStart to the current time.
    fd_table[fd].writeStart = squid_curtime;

    if (len == 0) {
        /* Note we even call write if nleft == 0 */
        /* We're done */
        if (nleft != 0)
            debugs(5, DBG_IMPORTANT, "FD " << fd << " write failure: connection closed with " << nleft << " bytes remaining.");

        state->finish(nleft ? Comm::COMM_ERROR : Comm::OK, 0);
    } else if (len < 0) {
        /* An error */
        if (fd_table[fd].flags.socket_eof) {
            debugs(50, 2, "FD " << fd << " write failure: " << xstrerr(xerrno) << ".");
            state->finish(nleft ? Comm::COMM_ERROR : Comm::OK, xerrno);
        } else if (ignoreErrno(xerrno)) {
            debugs(50, 9, "FD " << fd << " write failure: " << xstrerr(xerrno) << ".");
            state->selectOrQueueWrite();
        } else {
            debugs(50, 2, "FD " << fd << " write failure: " << xstrerr(xerrno) << ".");
            state->finish(nleft ? Comm::COMM_ERROR : Comm::OK, xerrno);
        }
    } else {
        /* A successful write, continue */
        state->offset += len;

        if (state->offset < state->size) {
            /* Not done, reinstall the write handler and write some more */
            state->selectOrQueueWrite();
        } else {
            state->finish(nleft ? Comm::OK : Comm::COMM_ERROR, 0);
        }
    }

    PROF_stop(commHandleWrite);
}