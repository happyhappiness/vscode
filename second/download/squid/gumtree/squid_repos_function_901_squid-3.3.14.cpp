int
commUnsetNonBlocking(int fd)
{
#if _SQUID_WINDOWS_
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
        debugs(50, DBG_IMPORTANT, "commSetTcpNoDelay: FD " << fd << ": " << xstrerror());

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
            debugs(5, DBG_IMPORTANT, "commSetKeepalive: FD " << fd << ": " << xstrerror());
    }
#endif
#ifdef TCP_KEEPIDLE
    if (idle) {
        if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE, &idle, sizeof(on)) < 0)
            debugs(5, DBG_IMPORTANT, "commSetKeepalive: FD " << fd << ": " << xstrerror());
    }
#endif
#ifdef TCP_KEEPINTVL
    if (interval) {
        if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPINTVL, &interval, sizeof(on)) < 0)
            debugs(5, DBG_IMPORTANT, "commSetKeepalive: FD " << fd << ": " << xstrerror());
    }
#endif
    if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *) &on, sizeof(on)) < 0)
        debugs(5, DBG_IMPORTANT, "commSetKeepalive: FD " << fd << ": " << xstrerror());
}

void
comm_init(void)
{
    fd_table =(fde *) xcalloc(Squid_MaxFD, sizeof(fde));
    fdd_table = (fd_debug_t *)xcalloc(Squid_MaxFD, sizeof(fd_debug_t));

    /* make sure the accept() socket FIFO delay queue exists */
    Comm::AcceptLimiter::Instance();

    // make sure the IO pending callback table exists
    Comm::CallbackTableInit();

    /* XXX account fd_table */
    /* Keep a few file descriptors free so that we don't run out of FD's
     * after accepting a client but before it opens a socket or a file.
     * Since Squid_MaxFD can be as high as several thousand, don't waste them */
    RESERVED_FD = min(100, Squid_MaxFD / 4);

    TheHalfClosed = new DescriptorSet;

    /* setup the select loop module */
    Comm::SelectLoopInit();
}

void
comm_exit(void)
{
    delete TheHalfClosed;
    TheHalfClosed = NULL;

    safe_free(fd_table);
    safe_free(fdd_table);
    Comm::CallbackTableDestruct();
}

#if USE_DELAY_POOLS
// called when the queue is done waiting for the client bucket to fill
void
commHandleWriteHelper(void * data)
{
    CommQuotaQueue *queue = static_cast<CommQuotaQueue*>(data);
    assert(queue);

    ClientInfo *clientInfo = queue->clientInfo;
    // ClientInfo invalidates queue if freed, so if we got here through,
    // evenAdd cbdata protections, everything should be valid and consistent
    assert(clientInfo);
    assert(clientInfo->hasQueue());
    assert(clientInfo->hasQueue(queue));
    assert(!clientInfo->selectWaiting);
    assert(clientInfo->eventWaiting);
    clientInfo->eventWaiting = false;

    do {
        // check that the head descriptor is still relevant
        const int head = clientInfo->quotaPeekFd();
        Comm::IoCallback *ccb = COMMIO_FD_WRITECB(head);

        if (fd_table[head].clientInfo == clientInfo &&
                clientInfo->quotaPeekReserv() == ccb->quotaQueueReserv &&
                !fd_table[head].closing()) {

            // wait for the head descriptor to become ready for writing
            Comm::SetSelect(head, COMM_SELECT_WRITE, Comm::HandleWrite, ccb, 0);
            clientInfo->selectWaiting = true;
            return;
        }

        clientInfo->quotaDequeue(); // remove the no longer relevant descriptor
        // and continue looking for a relevant one
    } while (clientInfo->hasQueue());

    debugs(77,3, HERE << "emptied queue");
}

bool
ClientInfo::hasQueue() const
{
    assert(quotaQueue);
    return !quotaQueue->empty();
}

bool
ClientInfo::hasQueue(const CommQuotaQueue *q) const
{
    assert(quotaQueue);
    return quotaQueue == q;
}

/// returns the first descriptor to be dequeued
int
ClientInfo::quotaPeekFd() const
{
    assert(quotaQueue);
    return quotaQueue->front();
}

/// returns the reservation ID of the first descriptor to be dequeued
unsigned int
ClientInfo::quotaPeekReserv() const
{
    assert(quotaQueue);
    return quotaQueue->outs + 1;
}

/// queues a given fd, creating the queue if necessary; returns reservation ID
unsigned int
ClientInfo::quotaEnqueue(int fd)
{
    assert(quotaQueue);
    return quotaQueue->enqueue(fd);
}

/// removes queue head
void
ClientInfo::quotaDequeue()
{
    assert(quotaQueue);
    quotaQueue->dequeue();
}

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

/// calculates how much to write for a single dequeued client
int
ClientInfo::quotaForDequed()
{
    /* If we have multiple clients and give full bucketSize to each client then
     * clt1 may often get a lot more because clt1->clt2 time distance in the
     * select(2) callback order may be a lot smaller than cltN->clt1 distance.
     * We divide quota evenly to be more fair. */

    if (!rationedCount) {
        rationedCount = quotaQueue->size() + 1;

        // The delay in ration recalculation _temporary_ deprives clients from
        // bytes that should have trickled in while rationedCount was positive.
        refillBucket();

        // Rounding errors do not accumulate here, but we round down to avoid
        // negative bucket sizes after write with rationedCount=1.
        rationedQuota = static_cast<int>(floor(bucketSize/rationedCount));
        debugs(77,5, HERE << "new rationedQuota: " << rationedQuota <<
               '*' << rationedCount);
    }

    --rationedCount;
    debugs(77,7, HERE << "rationedQuota: " << rationedQuota <<
           " rations remaining: " << rationedCount);

    // update 'last seen' time to prevent clientdb GC from dropping us
    last_seen = squid_curtime;
    return rationedQuota;
}

///< adds bytes to the quota bucket based on the rate and passed time
void
ClientInfo::refillBucket()
{
    // all these times are in seconds, with double precision
    const double currTime = current_dtime;
    const double timePassed = currTime - prevTime;

    // Calculate allowance for the time passed. Use double to avoid
    // accumulating rounding errors for small intervals. For example, always
    // adding 1 byte instead of 1.4 results in 29% bandwidth allocation error.
    const double gain = timePassed * writeSpeedLimit;

    debugs(77,5, HERE << currTime << " clt" << (const char*)hash.key << ": " <<
           bucketSize << " + (" << timePassed << " * " << writeSpeedLimit <<
           " = " << gain << ')');

    // to further combat error accumulation during micro updates,
    // quit before updating time if we cannot add at least one byte
    if (gain < 1.0)
        return;

    prevTime = currTime;

    // for "first" connections, drain initial fat before refilling but keep
    // updating prevTime to avoid bursts after the fat is gone
    if (bucketSize > bucketSizeLimit) {
        debugs(77,4, HERE << "not refilling while draining initial fat");
        return;
    }

    bucketSize += gain;

    // obey quota limits
    if (bucketSize > bucketSizeLimit)
        bucketSize = bucketSizeLimit;
}

void
ClientInfo::setWriteLimiter(const int aWriteSpeedLimit, const double anInitialBurst, const double aHighWatermark)
{
    debugs(77,5, HERE << "Write limits for " << (const char*)hash.key <<
           " speed=" << aWriteSpeedLimit << " burst=" << anInitialBurst <<
           " highwatermark=" << aHighWatermark);

    // set or possibly update traffic shaping parameters
    writeLimitingActive = true;
    writeSpeedLimit = aWriteSpeedLimit;
    bucketSizeLimit = aHighWatermark;

    // but some members should only be set once for a newly activated bucket
    if (firstTimeConnection) {
        firstTimeConnection = false;

        assert(!selectWaiting);
        assert(!quotaQueue);
        quotaQueue = new CommQuotaQueue(this);

        bucketSize = anInitialBurst;
        prevTime = current_dtime;
    }
}

CommQuotaQueue::CommQuotaQueue(ClientInfo *info): clientInfo(info),
        ins(0), outs(0)
{
    assert(clientInfo);
}

CommQuotaQueue::~CommQuotaQueue()
{
    assert(!clientInfo); // ClientInfo should clear this before destroying us
}

/// places the given fd at the end of the queue; returns reservation ID
unsigned int
CommQuotaQueue::enqueue(int fd)
{
    debugs(77,5, HERE << "clt" << (const char*)clientInfo->hash.key <<
           ": FD " << fd << " with qqid" << (ins+1) << ' ' << fds.size());
    fds.push_back(fd);
    return ++ins;
}

/// removes queue head
void
CommQuotaQueue::dequeue()
{
    assert(!fds.empty());
    debugs(77,5, HERE << "clt" << (const char*)clientInfo->hash.key <<
           ": FD " << fds.front() << " with qqid" << (outs+1) << ' ' <<
           fds.size());
    fds.pop_front();
    ++outs;
}
#endif

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

    for (fd = 0; fd <= Biggest_FD; ++fd) {
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
            old_comm_reset_close(fd);
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

static bool
writeTimedOut(int fd)
{
    if (!COMMIO_FD_WRITECB(fd)->active())
        return false;

    if ((squid_curtime - fd_table[fd].writeStart) < Config.Timeout.write)
        return false;

    return true;
}

void
checkTimeouts(void)
{
    int fd;
    fde *F = NULL;
    AsyncCall::Pointer callback;

    for (fd = 0; fd <= Biggest_FD; ++fd) {
        F = &fd_table[fd];

        if (writeTimedOut(fd)) {
            // We have an active write callback and we are timed out
            debugs(5, 5, "checkTimeouts: FD " << fd << " auto write timeout");
            Comm::SetSelect(fd, COMM_SELECT_WRITE, NULL, NULL, 0);
            COMMIO_FD_WRITECB(fd)->finish(COMM_ERROR, ETIMEDOUT);
        } else if (AlreadyTimedOut(F))
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

/// Start waiting for a possibly half-closed connection to close
// by scheduling a read callback to a monitoring handler that
// will close the connection on read errors.
void
commStartHalfClosedMonitor(int fd)
{
    debugs(5, 5, HERE << "adding FD " << fd << " to " << *TheHalfClosed);
    assert(isOpen(fd) && !commHasHalfClosedMonitor(fd));
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
        Comm::ConnectionPointer c = new Comm::Connection; // XXX: temporary. make HalfClosed a list of these.
        c->fd = *i;
        if (!fd_table[c->fd].halfClosedReader) { // not reading already
            AsyncCall::Pointer call = commCbCall(5,4, "commHalfClosedReader",
                                                 CommIoCbPtrFun(&commHalfClosedReader, NULL));
            comm_read(c, NULL, 0, call);
            fd_table[c->fd].halfClosedReader = call;
        } else
            c->fd = -1; // XXX: temporary. prevent c replacement erase closing listed FD
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
commHalfClosedReader(const Comm::ConnectionPointer &conn, char *, size_t size, comm_err_t flag, int, void *)
{
    // there cannot be more data coming in on half-closed connections
    assert(size == 0);
    assert(conn != NULL);
    assert(commHasHalfClosedMonitor(conn->fd)); // or we would have canceled the read

    fd_table[conn->fd].halfClosedReader = NULL; // done reading, for now

    // nothing to do if fd is being closed
    if (flag == COMM_ERR_CLOSING)
        return;

    // if read failed, close the connection
    if (flag != COMM_OK) {
        debugs(5, 3, HERE << "closing " << conn);
        conn->close();
        return;
    }

    // continue waiting for close or error
    commPlanHalfClosedCheck(); // make sure this fd will be checked again
}

CommRead::CommRead() : conn(NULL), buf(NULL), len(0), callback(NULL) {}

CommRead::CommRead(const Comm::ConnectionPointer &c, char *buf_, int len_, AsyncCall::Pointer &callback_)
        : conn(c), buf(buf_), len(len_), callback(callback_) {}

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
    debugs(5, 3, "Adding deferred read on " << aRead.theRead.conn);
    CbDataList<DeferredRead> *temp = deferredReads.push_back(aRead);

    // We have to use a global function as a closer and point to temp
    // instead of "this" because DeferredReadManager is not a job and
    // is not even cbdata protected
    // XXX: and yet we use cbdata protection functions on it??
    AsyncCall::Pointer closer = commCbCall(5,4,
                                           "DeferredReadManager::CloseHandler",
                                           CommCloseCbPtrFun(&CloseHandler, temp));
    comm_add_close_handler(aRead.theRead.conn->fd, closer);
    temp->element.closer = closer; // remeber so that we can cancel
}

void
DeferredReadManager::CloseHandler(const CommCloseCbParams &params)
{
    if (!cbdataReferenceValid(params.data))
        return;

    CbDataList<DeferredRead> *temp = (CbDataList<DeferredRead> *)params.data;

    temp->element.closer = NULL;
    temp->element.markCancelled();
}

DeferredRead
DeferredReadManager::popHead(CbDataListContainer<DeferredRead> &deferredReads)
{
    assert (!deferredReads.empty());

    DeferredRead &read = deferredReads.head->element;

    // NOTE: at this point the connection has been paused/stalled for an unknown
    //       amount of time. We must re-validate that it is active and usable.

    // If the connection has been closed already. Cancel this read.
    if (!Comm::IsConnOpen(read.theRead.conn)) {
        if (read.closer != NULL) {
            read.closer->cancel("Connection closed before.");
            read.closer = NULL;
        }
        read.markCancelled();
    }

    if (!read.cancelled) {
        comm_remove_close_handler(read.theRead.conn->fd, read.closer);
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

    if (Comm::IsConnOpen(aRead.theRead.conn) && fd_table[aRead.theRead.conn->fd].closing())
        return;

    debugs(5, 3, "Kicking deferred read on " << aRead.theRead.conn);

    aRead.theReader(aRead.theContext, aRead.theRead);
}

void
DeferredRead::markCancelled()
{
    cancelled = true;
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

    switch (Comm::DoSelect(timeout)) {

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

/// Create a unix-domain socket (UDS) that only supports FD_MSGHDR I/O.
int
comm_open_uds(int sock_type,
              int proto,
              struct sockaddr_un* addr,
              int flags)
{
    // TODO: merge with comm_openex() when Ip::Address becomes NetAddress

    int new_socket;

    PROF_start(comm_open);
    /* Create socket for accepting new connections. */
    ++ statCounter.syscalls.sock.sockets;

    /* Setup the socket addrinfo details for use */
    struct addrinfo AI;
    AI.ai_flags = 0;
    AI.ai_family = PF_UNIX;
    AI.ai_socktype = sock_type;
    AI.ai_protocol = proto;
    AI.ai_addrlen = SUN_LEN(addr);
    AI.ai_addr = (sockaddr*)addr;
    AI.ai_canonname = NULL;
    AI.ai_next = NULL;

    debugs(50, 3, HERE << "Attempt open socket for: " << addr->sun_path);

    if ((new_socket = socket(AI.ai_family, AI.ai_socktype, AI.ai_protocol)) < 0) {
        /* Increase the number of reserved fd's if calls to socket()
         * are failing because the open file table is full.  This
         * limits the number of simultaneous clients */

        if (limitError(errno)) {
            debugs(50, DBG_IMPORTANT, HERE << "socket failure: " << xstrerror());
            fdAdjustReserved();
        } else {
            debugs(50, DBG_CRITICAL, HERE << "socket failure: " << xstrerror());
        }

        PROF_stop(comm_open);
        return -1;
    }

    debugs(50, 3, "Opened UDS FD " << new_socket << " : family=" << AI.ai_family << ", type=" << AI.ai_socktype << ", protocol=" << AI.ai_protocol);

    /* update fdstat */
    debugs(50, 5, HERE << "FD " << new_socket << " is a new socket");

    assert(!isOpen(new_socket));
    fd_open(new_socket, FD_MSGHDR, NULL);

    fdd_table[new_socket].close_file = NULL;

    fdd_table[new_socket].close_line = 0;

    fd_table[new_socket].sock_family = AI.ai_family;

    if (!(flags & COMM_NOCLOEXEC))
        commSetCloseOnExec(new_socket);

    if (flags & COMM_REUSEADDR)
        commSetReuseAddr(new_socket);

    if (flags & COMM_NONBLOCKING) {
        if (commSetNonBlocking(new_socket) != COMM_OK) {
            comm_close(new_socket);
            PROF_stop(comm_open);
            return -1;
        }
    }

    if (flags & COMM_DOBIND) {
        if (commBind(new_socket, AI) != COMM_OK) {
            comm_close(new_socket);
            PROF_stop(comm_open);
            return -1;
        }
    }

#ifdef TCP_NODELAY
    if (sock_type == SOCK_STREAM)
        commSetTcpNoDelay(new_socket);

#endif

    if (Config.tcpRcvBufsz > 0 && sock_type == SOCK_STREAM)
        commSetTcpRcvbuf(new_socket, Config.tcpRcvBufsz);

    PROF_stop(comm_open);

    return new_socket;
}