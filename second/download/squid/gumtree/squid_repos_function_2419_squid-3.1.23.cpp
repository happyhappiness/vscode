void
FwdState::dispatch()
{
    peer *p = NULL;
    debugs(17, 3, "fwdDispatch: FD " << client_fd << ": Fetching '" << RequestMethodStr(request->method) << " " << entry->url() << "'" );
    /*
     * Assert that server_fd is set.  This is to guarantee that fwdState
     * is attached to something and will be deallocated when server_fd
     * is closed.
     */
    assert(server_fd > -1);

    fd_note(server_fd, entry->url());

    fd_table[server_fd].noteUse(fwdPconnPool);

    /*assert(!EBIT_TEST(entry->flags, ENTRY_DISPATCHED)); */
    assert(entry->ping_status != PING_WAITING);

    assert(entry->lock_count);

    EBIT_SET(entry->flags, ENTRY_DISPATCHED);

    netdbPingSite(request->GetHost());

#if USE_ZPH_QOS && defined(_SQUID_LINUX_)
    /* Bug 2537: This part of ZPH only applies to patched Linux kernels. */

    /* Retrieves remote server TOS value, and stores it as part of the
     * original client request FD object. It is later used to forward
     * remote server's TOS in the response to the client in case of a MISS.
     */
    fde * clientFde = &fd_table[client_fd];
    if (clientFde) {
        int tos = 1;
        int tos_len = sizeof(tos);
        clientFde->upstreamTOS = 0;
        if (setsockopt(server_fd,SOL_IP,IP_RECVTOS,&tos,tos_len)==0) {
            unsigned char buf[512];
            int len = 512;
            if (getsockopt(server_fd,SOL_IP,IP_PKTOPTIONS,buf,(socklen_t*)&len) == 0) {
                /* Parse the PKTOPTIONS structure to locate the TOS data message
                 * prepared in the kernel by the ZPH incoming TCP TOS preserving
                 * patch.
                 */
                unsigned char * pbuf = buf;
                while (pbuf-buf < len) {
                    struct cmsghdr *o = (struct cmsghdr*)pbuf;
                    if (o->cmsg_len<=0)
                        break;

                    if (o->cmsg_level == SOL_IP && o->cmsg_type == IP_TOS) {
                        int *tmp = (int*)CMSG_DATA(o);
                        clientFde->upstreamTOS = (unsigned char)*tmp;
                        break;
                    }
                    pbuf += CMSG_LEN(o->cmsg_len);
                }
            } else {
                debugs(33, 1, "ZPH: error in getsockopt(IP_PKTOPTIONS) on FD "<<server_fd<<" "<<xstrerror());
            }
        } else {
            debugs(33, 1, "ZPH: error in setsockopt(IP_RECVTOS) on FD "<<server_fd<<" "<<xstrerror());
        }
    }
#endif

    if (servers && (p = servers->_peer)) {
        p->stats.fetches++;
        request->peer_login = p->login;
        request->peer_domain = p->domain;
        httpStart(this);
    } else {
        request->peer_login = NULL;
        request->peer_domain = NULL;

        switch (request->protocol) {
#if USE_SSL

        case PROTO_HTTPS:
            httpStart(this);
            break;
#endif

        case PROTO_HTTP:
            httpStart(this);
            break;

        case PROTO_GOPHER:
            gopherStart(this);
            break;

        case PROTO_FTP:
            ftpStart(this);
            break;

        case PROTO_CACHEOBJ:

        case PROTO_INTERNAL:

        case PROTO_URN:
            fatal_dump("Should never get here");
            break;

        case PROTO_WHOIS:
            whoisStart(this);
            break;

        case PROTO_WAIS:	/* Not implemented */

        default:
            debugs(17, 1, "fwdDispatch: Cannot retrieve '" << entry->url() << "'" );
            ErrorState *anErr = errorCon(ERR_UNSUP_REQ, HTTP_BAD_REQUEST, request);
            fail(anErr);
            /*
             * Force a persistent connection to be closed because
             * some Netscape browsers have a bug that sends CONNECT
             * requests as GET's over persistent connections.
             */
            request->flags.proxy_keepalive = 0;
            /*
             * Set the dont_retry flag becuase this is not a
             * transient (network) error; its a bug.
             */
            flags.dont_retry = 1;
            comm_close(server_fd);
            break;
        }
    }
}