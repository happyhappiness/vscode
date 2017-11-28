        debugs(9, 9, HERE << ": found user='" << user << "'(" << total_len <<") unescaped.");
    }

    debugs(9, 9, HERE << ": OUT: login='" << login << "', escaped=" << escaped << ", user=" << user << ", password=" << password);
}

/**
 * Cancel the timeout on the Control socket and establish one
 * on the data socket
 */
void
FtpStateData::switchTimeoutToDataChannel()
{
    commUnsetConnTimeout(ctrl.conn);

    typedef CommCbMemFunT<FtpStateData, CommTimeoutCbParams> TimeoutDialer;
    AsyncCall::Pointer timeoutCall = JobCallback(9, 5, TimeoutDialer, this, FtpStateData::ftpTimeout);
    commSetConnTimeout(data.conn, Config.Timeout.read, timeoutCall);
}

void
FtpStateData::listenForDataChannel(const Comm::ConnectionPointer &conn, const char *note)
{
    assert(!Comm::IsConnOpen(data.conn));

    typedef CommCbMemFunT<FtpStateData, CommAcceptCbParams> AcceptDialer;
    typedef AsyncCallT<AcceptDialer> AcceptCall;
    RefCount<AcceptCall> call = static_cast<AcceptCall*>(JobCallback(11, 5, AcceptDialer, this, FtpStateData::ftpAcceptDataConnection));
    Subscription::Pointer sub = new CallSubscription<AcceptCall>(call);

    /* open the conn if its not already open */
    if (!Comm::IsConnOpen(conn)) {
        conn->fd = comm_open_listener(SOCK_STREAM, IPPROTO_TCP, conn->local, conn->flags, note);
        if (!Comm::IsConnOpen(conn)) {
            debugs(5, DBG_CRITICAL, HERE << "comm_open_listener failed:" << conn->local << " error: " << errno);
            return;
        }
        debugs(9, 3, HERE << "Unconnected data socket created on " << conn);
    }

    assert(Comm::IsConnOpen(conn));
    AsyncJob::Start(new Comm::TcpAcceptor(conn, note, sub));

    // Ensure we have a copy of the FD opened for listening and a close handler on it.
    data.opened(conn, dataCloser());
    switchTimeoutToDataChannel();
}

void
FtpStateData::ftpTimeout(const CommTimeoutCbParams &io)
{
    debugs(9, 4, HERE << io.conn << ": '" << entry->url() << "'" );

    if (abortOnBadEntry("entry went bad while waiting for a timeout"))
        return;

    if (SENT_PASV == state) {
        /* stupid ftp.netscape.com, of FTP server behind stupid firewall rules */
        flags.pasv_supported = false;
        debugs(9, DBG_IMPORTANT, "ftpTimeout: timeout in SENT_PASV state" );

        // cancel the data connection setup.
        if (data.opener != NULL) {
            data.opener->cancel("timeout");
            data.opener = NULL;
        }
        data.close();
    }

    failed(ERR_READ_TIMEOUT, 0);
    /* failed() closes ctrl.conn and frees ftpState */
}

#if DEAD_CODE // obsoleted by ERR_DIR_LISTING
void
FtpStateData::listingFinish()
{
    // TODO: figure out what this means and how to show it ...

    if (flags.listformat_unknown && !flags.tried_nlst) {
        printfReplyBody("<a href=\"%s/;type=d\">[As plain directory]</a>\n",
                        flags.dir_slash ? rfc1738_escape_part(old_filepath) : ".");
    } else if (typecode == 'D') {
        const char *path = flags.dir_slash ? filepath : ".";
        printfReplyBody("<a href=\"%s/\">[As extended directory]</a>\n", rfc1738_escape_part(path));
    }
}
#endif /* DEAD_CODE */

/// \ingroup ServerProtocolFTPInternal
static const char *Month[] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};
