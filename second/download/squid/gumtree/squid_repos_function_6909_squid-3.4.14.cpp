int
RFCNB_Get_Pkt(struct RFCNB_Con *con, struct RFCNB_Pkt *pkt, int len)
{
    int read_len, pkt_len;
    char hdr[RFCNB_Pkt_Hdr_Len];        /* Local space for the header */
    struct RFCNB_Pkt *pkt_frag;
    int more, this_time, offset, frag_len, this_len;
    BOOL seen_keep_alive = TRUE;

    /* Read that header straight into the buffer */

    if (len < RFCNB_Pkt_Hdr_Len) {      /* What a bozo */

#ifdef RFCNB_DEBUG
        fprintf(stderr, "Trying to read less than a packet:");
        perror("");
#endif
        RFCNB_errno = RFCNBE_BadParam;
        return (RFCNBE_Bad);

    }
    /* We discard keep alives here ... */

    if (RFCNB_Timeout > 0)
        alarm(RFCNB_Timeout);

    while (seen_keep_alive) {

        if ((read_len = read(con->fd, hdr, sizeof(hdr))) < 0) {         /* Problems */
#ifdef RFCNB_DEBUG
            fprintf(stderr, "Reading the packet, we got:");
            perror("");
#endif
            if (errno == EINTR)
                RFCNB_errno = RFCNBE_Timeout;
            else
                RFCNB_errno = RFCNBE_BadRead;
            RFCNB_saved_errno = errno;
            return (RFCNBE_Bad);

        }
        /* Now we check out what we got */

        if (read_len == 0) {    /* Connection closed, send back eof?  */

#ifdef RFCNB_DEBUG
            fprintf(stderr, "Connection closed reading\n");
#endif

            if (errno == EINTR)
                RFCNB_errno = RFCNBE_Timeout;
            else
                RFCNB_errno = RFCNBE_ConGone;
            RFCNB_saved_errno = errno;
            return (RFCNBE_Bad);

        }
        if (RFCNB_Pkt_Type(hdr) == RFCNB_SESSION_KEEP_ALIVE) {

#ifdef RFCNB_DEBUG
            fprintf(stderr, "RFCNB KEEP ALIVE received\n");
#endif

        } else {
            seen_keep_alive = FALSE;
        }

    }

    /* What if we got less than or equal to a hdr size in bytes? */

    if (read_len < sizeof(hdr)) {       /* We got a small packet */

        /* Now we need to copy the hdr portion we got into the supplied packet */

        memcpy(pkt->data, hdr, read_len);       /*Copy data */

#ifdef RFCNB_DEBUG
        RFCNB_Print_Pkt(stderr, "rcvd", pkt, read_len);
#endif

        return (read_len);

    }
    /* Now, if we got at least a hdr size, alloc space for rest, if we need it */

    pkt_len = RFCNB_Pkt_Len(hdr);

#ifdef RFCNB_DEBUG
    fprintf(stderr, "Reading Pkt: Length = %i\n", pkt_len);
#endif

    /* Now copy in the hdr */

    memcpy(pkt->data, hdr, sizeof(hdr));

    /* Get the rest of the packet ... first figure out how big our buf is? */
    /* And make sure that we handle the fragments properly ... Sure should */
    /* use an iovec ...                                                    */

    if (len < pkt_len)          /* Only get as much as we have space for */
        more = len - RFCNB_Pkt_Hdr_Len;
    else
        more = pkt_len;

    this_time = 0;

    /* We read for each fragment ... */

    if (pkt->len == read_len) { /* If this frag was exact size */
        pkt_frag = pkt->next;   /* Stick next lot in next frag */
        offset = 0;             /* then we start at 0 in next  */
    } else {
        pkt_frag = pkt;         /* Otherwise use rest of this frag */
        offset = RFCNB_Pkt_Hdr_Len;     /* Otherwise skip the header       */
    }

    frag_len = pkt_frag->len;

    if (more <= frag_len)       /* If len left to get less than frag space */
        this_len = more;        /* Get the rest ...                        */
    else
        this_len = frag_len - offset;

    while (more > 0) {

        if ((this_time = read(con->fd, (pkt_frag->data) + offset, this_len)) <= 0) {    /* Problems */

            if (errno == EINTR) {

                RFCNB_errno = RFCNB_Timeout;

            } else {
                if (this_time < 0)
                    RFCNB_errno = RFCNBE_BadRead;
                else
                    RFCNB_errno = RFCNBE_ConGone;
            }

            RFCNB_saved_errno = errno;
            return (RFCNBE_Bad);

        }
#ifdef RFCNB_DEBUG
        fprintf(stderr, "Frag_Len = %i, this_time = %i, this_len = %i, more = %i\n", frag_len,
                this_time, this_len, more);
#endif

        read_len = read_len + this_time;        /* How much have we read ... */

        /* Now set up the next part */

        if (pkt_frag->next == NULL)
            break;              /* That's it here */

        pkt_frag = pkt_frag->next;
        this_len = pkt_frag->len;
        offset = 0;

        more = more - this_time;

    }

#ifdef RFCNB_DEBUG
    fprintf(stderr, "Pkt Len = %i, read_len = %i\n", pkt_len, read_len);
    RFCNB_Print_Pkt(stderr, "rcvd", pkt, read_len + sizeof(hdr));
#endif

    if (read_len < (pkt_len + sizeof(hdr))) {   /* Discard the rest */

        return (RFCNB_Discard_Rest(con, (pkt_len + sizeof(hdr)) - read_len));

    }
    if (RFCNB_Timeout > 0)
        alarm(0);               /* Reset that sucker */

    return (read_len + sizeof(RFCNB_Hdr));
}