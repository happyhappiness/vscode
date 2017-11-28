int
RFCNB_Recv(void *con_Handle, struct RFCNB_Pkt *Data, int Length)
{
    struct RFCNB_Pkt *pkt;
//    struct RFCNB_Hdr *hdr;
    int ret_len;

    if (con_Handle == NULL) {

        RFCNB_errno = RFCNBE_BadHandle;
        RFCNB_saved_errno = errno;
        return (RFCNBE_Bad);

    }
    /* Now get a packet from below. We allocate a header first */

    /* Plug in the header and send the data */

    pkt = RFCNB_Alloc_Pkt(RFCNB_Pkt_Hdr_Len);

    if (pkt == NULL) {

        RFCNB_errno = RFCNBE_NoSpace;
        RFCNB_saved_errno = errno;
        return (RFCNBE_Bad);

    }
    pkt->next = Data;           /* Plug in the data portion */

    if ((ret_len = RFCNB_Get_Pkt(con_Handle, pkt, Length + RFCNB_Pkt_Hdr_Len)) < 0) {

#ifdef RFCNB_DEBUG
        fprintf(stderr, "Bad packet return in RFCNB_Recv... \n");
#endif
        RFCNB_Free_Pkt(pkt);
        return (RFCNBE_Bad);

    }
    /* We should check that we go a message and not a keep alive */

    pkt->next = NULL;

    RFCNB_Free_Pkt(pkt);

    return (ret_len);
}