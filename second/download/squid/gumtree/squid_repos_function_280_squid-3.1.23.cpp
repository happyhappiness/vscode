int
RFCNB_Put_Pkt(struct RFCNB_Con *con, struct RFCNB_Pkt *pkt, int len)
{
    int len_sent, tot_sent, this_len;
    struct RFCNB_Pkt *pkt_ptr;
    char *this_data;
    int i;
    struct iovec io_list[10];	/* We should never have more      */
    /* If we do, this will blow up ... */

    /* Try to send the data ... We only send as many bytes as len claims */
    /* We should try to stuff it into an IOVEC and send as one write     */


    pkt_ptr = pkt;
    len_sent = tot_sent = 0;	/* Nothing sent so far */
    i = 0;

    while ((pkt_ptr != NULL) & (i < 10)) {	/* Watch that magic number! */

        this_len = pkt_ptr->len;
        this_data = pkt_ptr->data;
        if ((tot_sent + this_len) > len)
            this_len = len - tot_sent;	/* Adjust so we don't send too much */

        /* Now plug into the iovec ... */

        io_list[i].iov_len = this_len;
        io_list[i].iov_base = this_data;
        i++;

        tot_sent += this_len;

        if (tot_sent == len)
            break;		/* Let's not send too much */

        pkt_ptr = pkt_ptr->next;

    }

#ifdef RFCNB_DEBUG
    fprintf(stderr, "Frags = %i, tot_sent = %i\n", i, tot_sent);
#endif

    /* Set up an alarm if timeouts are set ... */

    if (RFCNB_Timeout > 0)
        alarm(RFCNB_Timeout);

    if ((len_sent = writev(con->fd, io_list, i)) < 0) {		/* An error */

        con->rfc_errno = errno;
        if (errno == EINTR)	/* We were interrupted ... */
            RFCNB_errno = RFCNBE_Timeout;
        else
            RFCNB_errno = RFCNBE_BadWrite;
        RFCNB_saved_errno = errno;
        return (RFCNBE_Bad);

    }
    if (len_sent < tot_sent) {	/* Less than we wanted */
        if (errno == EINTR)	/* We were interrupted */
            RFCNB_errno = RFCNBE_Timeout;
        else
            RFCNB_errno = RFCNBE_BadWrite;
        RFCNB_saved_errno = errno;
        return (RFCNBE_Bad);
    }
    if (RFCNB_Timeout > 0)
        alarm(0);		/* Reset that sucker */

#ifdef RFCNB_DEBUG

    fprintf(stderr, "Len sent = %i ...\n", len_sent);
    RFCNB_Print_Pkt(stderr, "sent", pkt, len_sent);	/* Print what send ... */

#endif

    return (len_sent);

}