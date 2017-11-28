int
commUnsetNonBlocking(int fd)
{
#ifdef _SQUID_MSWIN_
    int nonblocking = FALSE;

    if (ioctlsocket(fd, FIONBIO, (unsigned long *) &nonblocking) < 0) {
#else
    int flags;
    int dummy = 0;

    if ((flags = fcntl(fd, F_GETFL, dummy)) < 0) {
        debugs(50, 0, "FD " << fd << ": fcntl F_GETFL: " << xstrerror());
        return COMM_ERROR;
    }

    if (fcntl(fd, F_SETFL, flags & (~SQUID_NONBLOCK)) < 0) {
#endif
        debugs(50, 0, "commUnsetNonBlocking: FD " << fd << ": " << xstrerror());
        return COMM_ERROR;
    }

    fd_table[fd].flags.nonblocking = 0;
    return 0;
}

void
commSetCloseOnExec(int fd)
{
#ifdef FD_CLOEXEC
    int flags;
    int dummy = 0;

    if ((flags = fcntl(fd, F_GETFD, dummy)) < 0) {
        debugs(50, 0, "FD " << fd << ": fcntl F_GETFD: " << xstrerror());
        return;
    }

    if (fcntl(fd, F_SETFD, flags | FD_CLOEXEC) < 0)
        debugs(50, 0, "FD " << fd << ": set close-on-exec failed: " << xstrerror());

    fd_table[fd].flags.close_on_exec = 1;

#endif
}

#ifdef TCP_NODELAY
static void
commSetTcpNoDelay(int fd)
{
    int on = 1;

    if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char *) &on, sizeof(on)) < 0)
        debugs(50, 1, "commSetTcpNoDelay: FD " << fd << ": " << xstrerror());

    fd_table[fd].flags.nodelay = 1;
}

#endif

void
commSetTcpKeepalive(int fd, int idle, int interval, int timeout)
{
    int on = 1;
#ifdef TCP_KEEPCNT
    if (timeout && interval) {
        int count = (timeout + interval - 1) / interval;
        if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPCNT, &count, sizeof(on)) < 0)
            debugs(5, 1, "commSetKeepalive: FD " << fd << ": " << xstrerror());
    }
#endif
#ifdef TCP_KEEPIDLE
    if (idle) {
        if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE, &idle, sizeof(on)) < 0)
            debugs(5, 1, "commSetKeepalive: FD " << fd << ": " << xstrerror());
    }
#endif
#ifdef TCP_KEEPINTVL
    if (interval) {
        if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPINTVL, &interval, sizeof(on)) < 0)
            debugs(5, 1, "commSetKeepalive: FD " << fd << ": " << xstrerror());
    }
#endif
    if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *) &on, sizeof(on)) < 0)
        debugs(5, 1, "commSetKeepalive: FD " << fd << ": " << xstrerror());
}

void
comm_init(void)
{
    fd_table =(fde *) xcalloc(Squid_MaxFD, sizeof(fde));
    fdd_table = (fd_debug_t *)xcalloc(Squid_MaxFD, sizeof(fd_debug_t));

    fdc_table = new AcceptFD[Squid_MaxFD];
    for (int pos = 0; pos < Squid_MaxFD; ++pos) {
        fdc_table[pos] = AcceptFD(pos);
    }

    commfd_table = (comm_fd_t *) xcalloc(Squid_MaxFD, sizeof(comm_fd_t));
    for (int pos = 0; pos < Squid_MaxFD; pos++) {
        commfd_table[pos].fd = pos;
        commfd_table[pos].readcb.fd = pos;
        commfd_table[pos].readcb.type = IOCB_READ;
        commfd_table[pos].writecb.fd = pos;
        commfd_table[pos].writecb.type = IOCB_WRITE;
    }

    /* XXX account fd_table */
    /* Keep a few file descriptors free so that we don't run out of FD's
     * after accepting a client but before it opens a socket or a file.
     * Since Squid_MaxFD can be as high as several thousand, don't waste them */
    RESERVED_FD = min(100, Squid_MaxFD / 4);

    conn_close_pool = memPoolCreate("close_handler", sizeof(close_handler));

    TheHalfClosed = new DescriptorSet;
}

void
comm_exit(void)
{
    delete TheHalfClosed;
    TheHalfClosed = NULL;

    safe_free(fd_table);
    safe_free(fdd_table);
    if (fdc_table) {
        delete[] fdc_table;
        fdc_table = NULL;
    }
    safe_free(commfd_table);
}

/* Write to FD. */
static void
commHandleWrite(int fd, void *data)
{
    comm_io_callback_t *state = (comm_io_callback_t *)data;
    int len = 0;
    int nleft;

    assert(state == COMMIO_FD_WRITECB(fd));

    PROF_start(commHandleWrite);
    debugs(5, 5, "commHandleWrite: FD " << fd << ": off " <<
           (long int) state->offset << ", sz " << (long int) state->size << ".");

    nleft = state->size - state->offset;
    len = FD_WRITE_METHOD(fd, state->buf + state->offset, nleft);
    debugs(5, 5, "commHandleWrite: write() returns " << len);
    fd_bytes(fd, len, FD_WRITE);
    statCounter.syscalls.sock.writes++;

    if (len == 0) {
        /* Note we even call write if nleft == 0 */
        /* We're done */

        if (nleft != 0)
            debugs(5, 1, "commHandleWrite: FD " << fd << ": write failure: connection closed with " << nleft << " bytes remaining.");

        commio_finish_callback(fd, COMMIO_FD_WRITECB(fd), nleft ? COMM_ERROR : COMM_OK, errno);
    } else if (len < 0) {
        /* An error */

        if (fd_table[fd].flags.socket_eof) {
            debugs(50, 2, "commHandleWrite: FD " << fd << ": write failure: " << xstrerror() << ".");
            commio_finish_callback(fd, COMMIO_FD_WRITECB(fd), nleft ? COMM_ERROR : COMM_OK, errno);
        } else if (ignoreErrno(errno)) {
            debugs(50, 10, "commHandleWrite: FD " << fd << ": write failure: " << xstrerror() << ".");
            commSetSelect(fd,
                          COMM_SELECT_WRITE,
                          commHandleWrite,
                          state,
                          0);
        } else {
            debugs(50, 2, "commHandleWrite: FD " << fd << ": write failure: " << xstrerror() << ".");
            commio_finish_callback(fd, COMMIO_FD_WRITECB(fd), nleft ? COMM_ERROR : COMM_OK, errno);
        }
    } else {
        /* A successful write, continue */
        state->offset += len;

        if (state->offset < state->size) {
            /* Not done, reinstall the write handler and write some more */
            commSetSelect(fd,
                          COMM_SELECT_WRITE,
                          commHandleWrite,
                          state,
                          0);
        } else {
            commio_finish_callback(fd, COMMIO_FD_WRITECB(fd), nleft ? COMM_OK : COMM_ERROR, errno);
        }
    }

    PROF_stop(commHandleWrite);
}

/*
 * Queue a write. handler/handler_data are called when the write
 * completes, on error, or on file descriptor close.
 *
 * free_func is used to free the passed buffer when the write has completed.
 */
void
comm_write(int fd, const char *buf, int size, IOCB * handler, void *handler_data, FREE * free_func)
{
    AsyncCall::Pointer call = commCbCall(5,5, "SomeCommWriteHander",
                                         CommIoCbPtrFun(handler, handler_data));

    comm_write(fd, buf, size, call, free_func);
}

void
comm_write(int fd, const char *buf, int size, AsyncCall::Pointer &callback, FREE * free_func)
{
    debugs(5, 5, "comm_write: FD " << fd << ": sz " << size << ": asynCall " << callback);

    /* Make sure we are open, not closing, and not writing */
    assert(isOpen(fd));
    assert(!fd_table[fd].closing());
    comm_io_callback_t *ccb = COMMIO_FD_WRITECB(fd);
    assert(!ccb->active());

    /* Queue the write */
    commio_set_callback(fd, IOCB_WRITE, ccb, callback,
                        (char *)buf, free_func, size);
    commSetSelect(fd, COMM_SELECT_WRITE, commHandleWrite, ccb, 0);
}


/* a wrapper around comm_write to allow for MemBuf to be comm_written in a snap */
void
comm_write_mbuf(int fd, MemBuf *mb, IOCB * handler, void *handler_data)
{
    comm_write(fd, mb->buf, mb->size, handler, handler_data, mb->freeFunc());
}

void
comm_write_mbuf(int fd, MemBuf *mb, AsyncCall::Pointer &callback)
{
    comm_write(fd, mb->buf, mb->size, callback, mb->freeFunc());
}


/*
 * hm, this might be too general-purpose for all the places we'd
 * like to use it.
 */
int
ignoreErrno(int ierrno)
{
    switch (ierrno) {

    case EINPROGRESS:

    case EWOULDBLOCK:
#if EAGAIN != EWOULDBLOCK

    case EAGAIN:
#endif

    case EALREADY:

    case EINTR:
#ifdef ERESTART

    case ERESTART:
#endif

        return 1;

    default:
        return 0;
    }

    /* NOTREACHED */
}

void
commCloseAllSockets(void)
{
    int fd;
    fde *F = NULL;

    for (fd = 0; fd <= Biggest_FD; fd++) {
        F = &fd_table[fd];

        if (!F->flags.open)
            continue;

        if (F->type != FD_SOCKET)
            continue;

        if (F->flags.ipc)	/* don't close inter-process sockets */
            continue;

        if (F->timeoutHandler != NULL) {
            AsyncCall::Pointer callback = F->timeoutHandler;
            F->timeoutHandler = NULL;
            debugs(5, 5, "commCloseAllSockets: FD " << fd << ": Calling timeout handler");
            ScheduleCallHere(callback);
        } else {
            debugs(5, 5, "commCloseAllSockets: FD " << fd << ": calling comm_reset_close()");
            comm_reset_close(fd);
        }
    }
}

static bool
AlreadyTimedOut(fde *F)
{
    if (!F->flags.open)
        return true;

    if (F->timeout == 0)
        return true;

    if (F->timeout > squid_curtime)
        return true;

    return false;
}

void
checkTimeouts(void)
{
    int fd;
    fde *F = NULL;
    AsyncCall::Pointer callback;

    for (fd = 0; fd <= Biggest_FD; fd++) {
        F = &fd_table[fd];

        if (AlreadyTimedOut(F))
            continue;

        debugs(5, 5, "checkTimeouts: FD " << fd << " Expired");

        if (F->timeoutHandler != NULL) {
            debugs(5, 5, "checkTimeouts: FD " << fd << ": Call timeout handler");
            callback = F->timeoutHandler;
            F->timeoutHandler = NULL;
            ScheduleCallHere(callback);
        } else {
            debugs(5, 5, "checkTimeouts: FD " << fd << ": Forcing comm_close()");
            comm_close(fd);
        }
    }
}

/*
 * New-style listen and accept routines
 *
 * Listen simply registers our interest in an FD for listening,
 * and accept takes a callback to call when an FD has been
 * accept()ed.
 */
int
comm_listen(int sock)
{
    int x;

    if ((x = listen(sock, Squid_MaxFD >> 2)) < 0) {
        debugs(50, 0, "comm_listen: listen(" << (Squid_MaxFD >> 2) << ", " << sock << "): " << xstrerror());
        return x;
    }

    if (Config.accept_filter && strcmp(Config.accept_filter, "none") != 0) {
#ifdef SO_ACCEPTFILTER
        struct accept_filter_arg afa;
        bzero(&afa, sizeof(afa));
        debugs(5, DBG_CRITICAL, "Installing accept filter '" << Config.accept_filter << "' on FD " << sock);
        xstrncpy(afa.af_name, Config.accept_filter, sizeof(afa.af_name));
        x = setsockopt(sock, SOL_SOCKET, SO_ACCEPTFILTER, &afa, sizeof(afa));
        if (x < 0)
            debugs(5, 0, "SO_ACCEPTFILTER '" << Config.accept_filter << "': '" << xstrerror());
#elif defined(TCP_DEFER_ACCEPT)
        int seconds = 30;
        if (strncmp(Config.accept_filter, "data=", 5) == 0)
            seconds = atoi(Config.accept_filter + 5);
        x = setsockopt(sock, IPPROTO_TCP, TCP_DEFER_ACCEPT, &seconds, sizeof(seconds));
        if (x < 0)
            debugs(5, 0, "TCP_DEFER_ACCEPT '" << Config.accept_filter << "': '" << xstrerror());
#else
        debugs(5, 0, "accept_filter not supported on your OS");
#endif
    }

    return sock;
}

void
comm_accept(int fd, IOACB *handler, void *handler_data)
{
    debugs(5, 5, "comm_accept: FD " << fd << " handler: " << (void*)handler);
    assert(isOpen(fd));

    AsyncCall::Pointer call = commCbCall(5,5, "SomeCommAcceptHandler",
                                         CommAcceptCbPtrFun(handler, handler_data));
    fdc_table[fd].subscribe(call);
}

void
comm_accept(int fd, AsyncCall::Pointer &call)
{
    debugs(5, 5, "comm_accept: FD " << fd << " AsyncCall: " << call);
    assert(isOpen(fd));

    fdc_table[fd].subscribe(call);
}

// Called when somebody wants to be notified when our socket accepts new
// connection. We do not probe the FD until there is such interest.
void
AcceptFD::subscribe(AsyncCall::Pointer &call)
{
    /* make sure we're not pending! */
    assert(!theCallback);
    theCallback = call;

#if OPTIMISTIC_IO
    mayAcceptMore = true; // even if we failed to accept last time
#endif

    if (mayAcceptMore)
        acceptNext();
    else
        commSetSelect(fd, COMM_SELECT_READ, comm_accept_try, NULL, 0);
}

void
AcceptFD::acceptOne()
{
    // If there is no callback and we accept, we will leak the accepted FD.
    // When we are running out of FDs, there is often no callback.
    if (!theCallback) {
        debugs(5, 5, "AcceptFD::acceptOne orphaned: FD " << fd);
        // XXX: can we remove this and similar "just in case" calls and
        // either listen always or listen only when there is a callback?
        if (!AcceptLimiter::Instance().deferring())
            commSetSelect(fd, COMM_SELECT_READ, comm_accept_try, NULL, 0);
        mayAcceptMore = false;
        return;
    }

    /*
     * We don't worry about running low on FDs here.  Instead,
     * httpAccept() will use AcceptLimiter if we reach the limit
     * there.
     */

    /* Accept a new connection */
    ConnectionDetail connDetails;
    int newfd = comm_old_accept(fd, connDetails);

    /* Check for errors */

    if (newfd < 0) {
        assert(theCallback != NULL);

        if (newfd == COMM_NOMESSAGE) {
            /* register interest again */
            debugs(5, 5, HERE << "try later: FD " << fd <<
                   " handler: " << theCallback);
            commSetSelect(fd, COMM_SELECT_READ, comm_accept_try, NULL, 0);
            return;
        }

        // A non-recoverable error; notify the caller */
        notify(-1, COMM_ERROR, errno, connDetails);
        mayAcceptMore = false;
        return;
    }

    assert(theCallback != NULL);
    debugs(5, 5, "AcceptFD::acceptOne accepted: FD " << fd <<
           " newfd: " << newfd << " from: " << connDetails.peer <<
           " handler: " << *theCallback);
    notify(newfd, COMM_OK, 0, connDetails);
    mayAcceptMore = true;
}

void
AcceptFD::acceptNext()
{
    acceptOne();
}

void
AcceptFD::notify(int newfd, comm_err_t errcode, int xerrno, const ConnectionDetail &connDetails)
{
    if (theCallback != NULL) {
        typedef CommAcceptCbParams Params;
        Params &params = GetCommParams<Params>(theCallback);
        params.fd = fd;
        params.nfd = newfd;
        params.details = connDetails;
        params.flag = errcode;
        params.xerrno = xerrno;
        ScheduleCallHere(theCallback);
        theCallback = NULL;
    }
}

/*
 * This callback is called whenever a filedescriptor is ready
 * to dupe itself and fob off an accept()ed connection
 */
static void
comm_accept_try(int fd, void *)
{
    assert(isOpen(fd));
    fdc_table[fd].acceptNext();
}

void
CommIO::Initialize()
{
    if (CommIO::Initialized)
        return;

    /* Initialize done pipe signal */
    int DonePipe[2];
    if (pipe(DonePipe)) {}
    DoneFD = DonePipe[1];
    DoneReadFD = DonePipe[0];
    fd_open(DoneReadFD, FD_PIPE, "async-io completion event: main");
    fd_open(DoneFD, FD_PIPE, "async-io completion event: threads");
    commSetNonBlocking(DoneReadFD);
    commSetNonBlocking(DoneFD);
    commSetSelect(DoneReadFD, COMM_SELECT_READ, NULLFDHandler, NULL, 0);
    Initialized = true;
}

void CommIO::NotifyIOClose()
{
    /* Close done pipe signal */
    FlushPipe();
    close(DoneFD);
    close(DoneReadFD);
    fd_close(DoneFD);
    fd_close(DoneReadFD);
    Initialized = false;
}

bool CommIO::Initialized = false;
bool CommIO::DoneSignalled = false;
int CommIO::DoneFD = -1;
int CommIO::DoneReadFD = -1;

void
CommIO::FlushPipe()
{
    char buf[256];
    FD_READ_METHOD(DoneReadFD, buf, sizeof(buf));
}

void
CommIO::NULLFDHandler(int fd, void *data)
{
    FlushPipe();
    commSetSelect(fd, COMM_SELECT_READ, NULLFDHandler, NULL, 0);
}

void
CommIO::ResetNotifications()
{
    if (DoneSignalled) {
        FlushPipe();
        DoneSignalled = false;
    }
}

AcceptLimiter AcceptLimiter::Instance_;

AcceptLimiter &AcceptLimiter::Instance()
{
    return Instance_;
}

bool
AcceptLimiter::deferring() const
{
    return deferred.size() > 0;
}

void
AcceptLimiter::defer (int fd, Acceptor::AcceptorFunction *aFunc, void *data)
{
    debugs(5, 5, "AcceptLimiter::defer: FD " << fd << " handler: " << (void*)aFunc);
    Acceptor temp;
    temp.theFunction = aFunc;
    temp.acceptFD = fd;
    temp.theData = data;
    deferred.push_back(temp);
}

void
AcceptLimiter::kick()
{
    if (!deferring())
        return;

    /* Yes, this means the first on is the last off....
     * If the list container was a little more friendly, we could sensibly us it.
     */
    Acceptor temp = deferred.pop_back();

    comm_accept (temp.acceptFD, temp.theFunction, temp.theData);
}

/// Start waiting for a possibly half-closed connection to close
// by scheduling a read callback to a monitoring handler that
// will close the connection on read errors.
void
commStartHalfClosedMonitor(int fd)
{
    debugs(5, 5, HERE << "adding FD " << fd << " to " << *TheHalfClosed);
    assert(isOpen(fd));
    assert(!commHasHalfClosedMonitor(fd));
    (void)TheHalfClosed->add(fd); // could also assert the result
    commPlanHalfClosedCheck(); // may schedule check if we added the first FD
}

static
void
commPlanHalfClosedCheck()
{
    if (!WillCheckHalfClosed && !TheHalfClosed->empty()) {
        eventAdd("commHalfClosedCheck", &commHalfClosedCheck, NULL, 1.0, 1);
        WillCheckHalfClosed = true;
    }
}

/// iterates over all descriptors that may need half-closed tests and
/// calls comm_read for those that do; re-schedules the check if needed
static
void
commHalfClosedCheck(void *)
{
    debugs(5, 5, HERE << "checking " << *TheHalfClosed);

    typedef DescriptorSet::const_iterator DSCI;
    const DSCI end = TheHalfClosed->end();
    for (DSCI i = TheHalfClosed->begin(); i != end; ++i) {
        const int fd = *i;
        if (!fd_table[fd].halfClosedReader) { // not reading already
            AsyncCall::Pointer call = commCbCall(5,4, "commHalfClosedReader",
                                                 CommIoCbPtrFun(&commHalfClosedReader, NULL));
            comm_read(fd, NULL, 0, call);
            fd_table[fd].halfClosedReader = call;
        }
    }

    WillCheckHalfClosed = false; // as far as we know
    commPlanHalfClosedCheck(); // may need to check again
}

/// checks whether we are waiting for possibly half-closed connection to close
// We are monitoring if the read handler for the fd is the monitoring handler.
bool
commHasHalfClosedMonitor(int fd)
{
    return TheHalfClosed->has(fd);
}

/// stop waiting for possibly half-closed connection to close
static void
commStopHalfClosedMonitor(int const fd)
{
    debugs(5, 5, HERE << "removing FD " << fd << " from " << *TheHalfClosed);

    // cancel the read if one was scheduled
    AsyncCall::Pointer reader = fd_table[fd].halfClosedReader;
    if (reader != NULL)
        comm_read_cancel(fd, reader);
    fd_table[fd].halfClosedReader = NULL;

    TheHalfClosed->del(fd);
}

/// I/O handler for the possibly half-closed connection monitoring code
static void
commHalfClosedReader(int fd, char *, size_t size, comm_err_t flag, int, void *)
{
    // there cannot be more data coming in on half-closed connections
    assert(size == 0);
    assert(commHasHalfClosedMonitor(fd)); // or we would have canceled the read

    fd_table[fd].halfClosedReader = NULL; // done reading, for now

    // nothing to do if fd is being closed
    if (flag == COMM_ERR_CLOSING)
        return;

    // if read failed, close the connection
    if (flag != COMM_OK) {
        debugs(5, 3, "commHalfClosedReader: closing FD " << fd);
        comm_close(fd);
        return;
    }

    // continue waiting for close or error
    commPlanHalfClosedCheck(); // make sure this fd will be checked again
}


CommRead::CommRead() : fd(-1), buf(NULL), len(0), callback(NULL) {}

CommRead::CommRead(int fd_, char *buf_, int len_, AsyncCall::Pointer &callback_)
        : fd(fd_), buf(buf_), len(len_), callback(callback_) {}

DeferredRead::DeferredRead () : theReader(NULL), theContext(NULL), theRead(), cancelled(false) {}

DeferredRead::DeferredRead (DeferrableRead *aReader, void *data, CommRead const &aRead) : theReader(aReader), theContext (data), theRead(aRead), cancelled(false) {}

DeferredReadManager::~DeferredReadManager()
{
    flushReads();
    assert (deferredReads.empty());
}

/* explicit instantiation required for some systems */

/// \cond AUTODOCS-IGNORE
template cbdata_type CbDataList<DeferredRead>::CBDATA_CbDataList;
/// \endcond

void
DeferredReadManager::delayRead(DeferredRead const &aRead)
{
    debugs(5, 3, "Adding deferred read on FD " << aRead.theRead.fd);
    CbDataList<DeferredRead> *temp = deferredReads.push_back(aRead);

    // We have to use a global function as a closer and point to temp
    // instead of "this" because DeferredReadManager is not a job and
    // is not even cbdata protected
    AsyncCall::Pointer closer = commCbCall(5,4,
                                           "DeferredReadManager::CloseHandler",
                                           CommCloseCbPtrFun(&CloseHandler, temp));
    comm_add_close_handler(aRead.theRead.fd, closer);
    temp->element.closer = closer; // remeber so that we can cancel
}

void
DeferredReadManager::CloseHandler(int fd, void *thecbdata)
{
    if (!cbdataReferenceValid (thecbdata))
        return;

    CbDataList<DeferredRead> *temp = (CbDataList<DeferredRead> *)thecbdata;

    temp->element.closer = NULL;
    temp->element.markCancelled();
}

DeferredRead
DeferredReadManager::popHead(CbDataListContainer<DeferredRead> &deferredReads)
{
    assert (!deferredReads.empty());

    DeferredRead &read = deferredReads.head->element;
    if (!read.cancelled) {
        comm_remove_close_handler(read.theRead.fd, read.closer);
        read.closer = NULL;
    }

    DeferredRead result = deferredReads.pop_front();

    return result;
}

void
DeferredReadManager::kickReads(int const count)
{
    /* if we had CbDataList::size() we could consolidate this and flushReads */

    if (count < 1) {
        flushReads();
        return;
    }

    size_t remaining = count;

    while (!deferredReads.empty() && remaining) {
        DeferredRead aRead = popHead(deferredReads);
        kickARead(aRead);

        if (!aRead.cancelled)
            --remaining;
    }
}

void
DeferredReadManager::flushReads()
{
    CbDataListContainer<DeferredRead> reads;
    reads = deferredReads;
    deferredReads = CbDataListContainer<DeferredRead>();

    // XXX: For fairness this SHOULD randomize the order
    while (!reads.empty()) {
        DeferredRead aRead = popHead(reads);
        kickARead(aRead);
    }
}

void
DeferredReadManager::kickARead(DeferredRead const &aRead)
{
    if (aRead.cancelled)
        return;

    if (aRead.theRead.fd>=0 && fd_table[aRead.theRead.fd].closing())
        return;

    debugs(5, 3, "Kicking deferred read on FD " << aRead.theRead.fd);

    aRead.theReader(aRead.theContext, aRead.theRead);
}

void
DeferredRead::markCancelled()
{
    cancelled = true;
}

ConnectionDetail::ConnectionDetail() : me(), peer()
{
}

int
CommSelectEngine::checkEvents(int timeout)
{
    static time_t last_timeout = 0;

    /* No, this shouldn't be here. But it shouldn't be in each comm handler. -adrian */
    if (squid_curtime > last_timeout) {
        last_timeout = squid_curtime;
        checkTimeouts();
    }

    switch (comm_select(timeout)) {

    case COMM_OK:

    case COMM_TIMEOUT:
        return 0;

    case COMM_IDLE:

    case COMM_SHUTDOWN:
        return EVENT_IDLE;

    case COMM_ERROR:
        return EVENT_ERROR;

    default:
        fatal_dump("comm.cc: Internal error -- this should never happen.");
        return EVENT_ERROR;
    };
}