int
rfc1035MessageUnpack(const char *buf,
                     size_t sz,
                     rfc1035_message ** answer)
{
    unsigned int off = 0;
    unsigned int i, j;
    unsigned int nr = 0;
    rfc1035_message *msg = NULL;
    rfc1035_rr *recs = NULL;
    rfc1035_query *querys = NULL;
    msg = (rfc1035_message*)xcalloc(1, sizeof(*msg));
    if (rfc1035HeaderUnpack(buf + off, sz - off, &off, msg)) {
        RFC1035_UNPACK_DEBUG;
        xfree(msg);
        return -rfc1035_unpack_error;
    }
    i = (unsigned int) msg->qdcount;
    if (i != 1) {
        /* This can not be an answer to our queries.. */
        RFC1035_UNPACK_DEBUG;
        xfree(msg);
        return -rfc1035_unpack_error;
    }
    querys = msg->query = (rfc1035_query*)xcalloc(i, sizeof(*querys));
    for (j = 0; j < i; j++) {
        if (rfc1035QueryUnpack(buf, sz, &off, &querys[j])) {
            RFC1035_UNPACK_DEBUG;
            rfc1035MessageDestroy(&msg);
            return -rfc1035_unpack_error;
        }
    }
    *answer = msg;
    if (msg->rcode) {
        RFC1035_UNPACK_DEBUG;
        return -msg->rcode;
    }
    if (msg->ancount == 0)
        return 0;
    i = (unsigned int) msg->ancount;
    recs = msg->answer = (rfc1035_rr*)xcalloc(i, sizeof(*recs));
    for (j = 0; j < i; j++) {
        if (off >= sz) {	/* corrupt packet */
            RFC1035_UNPACK_DEBUG;
            break;
        }
        if (rfc1035RRUnpack(buf, sz, &off, &recs[j])) {		/* corrupt RR */
            RFC1035_UNPACK_DEBUG;
            break;
        }
        nr++;
    }
    if (nr == 0) {
        /*
         * we expected to unpack some answers (ancount != 0), but
         * didn't actually get any.
         */
        rfc1035MessageDestroy(&msg);
        *answer = NULL;
        return -rfc1035_unpack_error;
    }
    return nr;
}