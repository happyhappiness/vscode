int
RFCNB_Send(struct RFCNB_Con *Con_Handle, struct RFCNB_Pkt *udata, int Length)
{
    struct RFCNB_Pkt *pkt;
    char *hdr;
    int len;

    /* Plug in the header and send the data */

    pkt = RFCNB_Alloc_Pkt(RFCNB_Pkt_Hdr_Len);

    if (pkt == NULL) {

        RFCNB_errno = RFCNBE_NoSpace;
        RFCNB_saved_errno = errno;
        return (RFCNBE_Bad);

    }
    pkt->next = udata;          /* The user data we want to send */

    hdr = pkt->data;

    /* Following crap is for portability across multiple UNIX machines */

    *(hdr + RFCNB_Pkt_Type_Offset) = RFCNB_SESSION_MESSAGE;
    RFCNB_Put_Pkt_Len(hdr, Length);

#ifdef RFCNB_DEBUG

    fprintf(stderr, "Sending packet: ");

#endif

    if ((len = RFCNB_Put_Pkt(Con_Handle, pkt, Length + RFCNB_Pkt_Hdr_Len)) < 0) {

        /* No need to change RFCNB_errno as it was done by put_pkt ...     */

        RFCNB_Free_Pkt(pkt);
        return (RFCNBE_Bad);    /* Should be able to write that lot ... */

    }
    /* Now we have sent that lot, let's get rid of the RFCNB Header and return */

    pkt->next = NULL;

    RFCNB_Free_Pkt(pkt);

    return (len);
}