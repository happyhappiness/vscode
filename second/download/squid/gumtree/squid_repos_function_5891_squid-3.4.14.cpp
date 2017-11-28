static void
netdbExchangeHandleReply(void *data, StoreIOBuffer receivedData)
{
    Ip::Address addr;

    netdbExchangeState *ex = (netdbExchangeState *)data;
    int rec_sz = 0;
    int o;

    struct in_addr line_addr;
    double rtt;
    double hops;
    char *p;
    int j;
    HttpReply const *rep;
    size_t hdr_sz;
    int nused = 0;
    int size;
    int oldbufofs = ex->buf_ofs;

    rec_sz = 0;
    rec_sz += 1 + sizeof(struct in_addr);
    rec_sz += 1 + sizeof(int);
    rec_sz += 1 + sizeof(int);
    debugs(38, 3, "netdbExchangeHandleReply: " << receivedData.length << " read bytes");

    if (!cbdataReferenceValid(ex->p)) {
        debugs(38, 3, "netdbExchangeHandleReply: Peer became invalid");
        netdbExchangeDone(ex);
        return;
    }

    debugs(38, 3, "netdbExchangeHandleReply: for '" << ex->p->host << ":" << ex->p->http_port << "'");

    if (receivedData.length == 0 &&
            !receivedData.flags.error) {
        debugs(38, 3, "netdbExchangeHandleReply: Done");
        netdbExchangeDone(ex);
        return;
    }

    p = ex->buf;

    /* Get the size of the buffer now */
    size = ex->buf_ofs + receivedData.length;
    debugs(38, 3, "netdbExchangeHandleReply: " << size << " bytes buf");

    /* Check if we're still doing headers */

    if (ex->connstate == STATE_HEADER) {

        ex->buf_ofs += receivedData.length;

        /* skip reply headers */

        if ((hdr_sz = headersEnd(p, ex->buf_ofs))) {
            debugs(38, 5, "netdbExchangeHandleReply: hdr_sz = " << hdr_sz);
            rep = ex->e->getReply();
            assert(rep->sline.status() != Http::scNone);
            debugs(38, 3, "netdbExchangeHandleReply: reply status " << rep->sline.status());

            if (rep->sline.status() != Http::scOkay) {
                netdbExchangeDone(ex);
                return;
            }

            assert((size_t)ex->buf_ofs >= hdr_sz);

            /*
             * Now, point p to the part of the buffer where the data
             * starts, and update the size accordingly
             */
            assert(ex->used == 0);
            ex->used = hdr_sz;
            size = ex->buf_ofs - hdr_sz;
            p += hdr_sz;

            /* Finally, set the conn state mode to STATE_BODY */
            ex->connstate = STATE_BODY;
        } else {
            StoreIOBuffer tempBuffer;
            tempBuffer.offset = ex->buf_ofs;
            tempBuffer.length = ex->buf_sz - ex->buf_ofs;
            tempBuffer.data = ex->buf + ex->buf_ofs;
            /* Have more headers .. */
            storeClientCopy(ex->sc, ex->e, tempBuffer,
                            netdbExchangeHandleReply, ex);
            return;
        }
    }

    assert(ex->connstate == STATE_BODY);

    /* If we get here, we have some body to parse .. */
    debugs(38, 5, "netdbExchangeHandleReply: start parsing loop, size = " << size);

    while (size >= rec_sz) {
        debugs(38, 5, "netdbExchangeHandleReply: in parsing loop, size = " << size);
        addr.setAnyAddr();
        hops = rtt = 0.0;

        for (o = 0; o < rec_sz;) {
            switch ((int) *(p + o)) {

            case NETDB_EX_NETWORK:
                ++o;
                /* FIXME INET6 : NetDB can still ony send IPv4 */
                memcpy(&line_addr, p + o, sizeof(struct in_addr));
                addr = line_addr;
                o += sizeof(struct in_addr);
                break;

            case NETDB_EX_RTT:
                ++o;
                memcpy(&j, p + o, sizeof(int));
                o += sizeof(int);
                rtt = (double) ntohl(j) / 1000.0;
                break;

            case NETDB_EX_HOPS:
                ++o;
                memcpy(&j, p + o, sizeof(int));
                o += sizeof(int);
                hops = (double) ntohl(j) / 1000.0;
                break;

            default:
                debugs(38, DBG_IMPORTANT, "netdbExchangeHandleReply: corrupt data, aborting");
                netdbExchangeDone(ex);
                return;
            }
        }

        if (!addr.isAnyAddr() && rtt > 0)
            netdbExchangeUpdatePeer(addr, ex->p, rtt, hops);

        assert(o == rec_sz);

        ex->used += rec_sz;

        size -= rec_sz;

        p += rec_sz;

        ++nused;
    }

    /*
     * Copy anything that is left over to the beginning of the buffer,
     * and adjust buf_ofs accordingly
     */

    /*
     * Evilly, size refers to the buf size left now,
     * ex->buf_ofs is the original buffer size, so just copy that
     * much data over
     */
    memmove(ex->buf, ex->buf + (ex->buf_ofs - size), size);

    ex->buf_ofs = size;

    /*
     * And don't re-copy the remaining data ..
     */
    ex->used += size;

    /*
     * Now the tricky bit - size _included_ the leftover bit from the _last_
     * storeClientCopy. We don't want to include that, or our offset will be wrong.
     * So, don't count the size of the leftover buffer we began with.
     * This can _disappear_ when we're not tracking offsets ..
     */
    ex->used -= oldbufofs;

    debugs(38, 3, "netdbExchangeHandleReply: size left over in this buffer: " << size << " bytes");

    debugs(38, 3, "netdbExchangeHandleReply: used " << nused <<
           " entries, (x " << rec_sz << " bytes) == " << nused * rec_sz <<
           " bytes total");

    debugs(38, 3, "netdbExchangeHandleReply: used " << ex->used);

    if (EBIT_TEST(ex->e->flags, ENTRY_ABORTED)) {
        debugs(38, 3, "netdbExchangeHandleReply: ENTRY_ABORTED");
        netdbExchangeDone(ex);
    } else if (ex->e->store_status == STORE_PENDING) {
        StoreIOBuffer tempBuffer;
        tempBuffer.offset = ex->used;
        tempBuffer.length = ex->buf_sz - ex->buf_ofs;
        tempBuffer.data = ex->buf + ex->buf_ofs;
        debugs(38, 3, "netdbExchangeHandleReply: EOF not received");
        storeClientCopy(ex->sc, ex->e, tempBuffer,
                        netdbExchangeHandleReply, ex);
    }
}