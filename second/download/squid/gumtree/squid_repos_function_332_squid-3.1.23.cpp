int
RFCNB_Session_Req(struct RFCNB_Con *con,
                  char *Called_Name,
                  char *Calling_Name,
                  BOOL * redirect,
                  struct in_addr *Dest_IP,
                  int *port)
{
    char *sess_pkt;

    /* Response packet should be no more than 9 bytes, make 16 jic */

    char resp[16];
    int len;
    struct RFCNB_Pkt *pkt, res_pkt;

    /* We build and send the session request, then read the response */

    pkt = RFCNB_Alloc_Pkt(RFCNB_Pkt_Sess_Len);

    if (pkt == NULL) {

        return (RFCNBE_Bad);	/* Leave the error that RFCNB_Alloc_Pkt gives) */

    }
    sess_pkt = pkt->data;	/* Get pointer to packet proper */

    sess_pkt[RFCNB_Pkt_Type_Offset] = RFCNB_SESSION_REQUEST;
    RFCNB_Put_Pkt_Len(sess_pkt, (RFCNB_Pkt_Sess_Len - RFCNB_Pkt_Hdr_Len));
    sess_pkt[RFCNB_Pkt_N1Len_Offset] = 32;
    sess_pkt[RFCNB_Pkt_N2Len_Offset] = 32;

    RFCNB_CvtPad_Name(Called_Name, (sess_pkt + RFCNB_Pkt_Called_Offset));
    RFCNB_CvtPad_Name(Calling_Name, (sess_pkt + RFCNB_Pkt_Calling_Offset));

    /* Now send the packet */

#ifdef RFCNB_DEBUG

    fprintf(stderr, "Sending packet: ");

#endif

    if ((len = RFCNB_Put_Pkt(con, pkt, RFCNB_Pkt_Sess_Len)) < 0) {

        return (RFCNBE_Bad);	/* Should be able to write that lot ... */

    }
#ifdef RFCNB_DEBUG

    fprintf(stderr, "Getting packet.\n");

#endif

    res_pkt.data = resp;
    res_pkt.len = sizeof(resp);
    res_pkt.next = NULL;

    if ((len = RFCNB_Get_Pkt(con, &res_pkt, sizeof(resp))) < 0) {

        return (RFCNBE_Bad);

    }
    /* Now analyze the packet ... */

    switch (RFCNB_Pkt_Type(resp)) {

    case RFCNB_SESSION_REJ:	/* Didnt like us ... too bad */

        /* Why did we get rejected ? */

        switch (CVAL(resp, RFCNB_Pkt_Error_Offset)) {

        case 0x80:
            RFCNB_errno = RFCNBE_CallRejNLOCN;
            break;
        case 0x81:
            RFCNB_errno = RFCNBE_CallRejNLFCN;
            break;
        case 0x82:
            RFCNB_errno = RFCNBE_CallRejCNNP;
            break;
        case 0x83:
            RFCNB_errno = RFCNBE_CallRejInfRes;
            break;
        case 0x8F:
            RFCNB_errno = RFCNBE_CallRejUnSpec;
            break;
        default:
            RFCNB_errno = RFCNBE_ProtErr;
            break;
        }

        return (RFCNBE_Bad);
        break;

    case RFCNB_SESSION_ACK:	/* Got what we wanted ...      */

        return (0);
        break;

    case RFCNB_SESSION_RETARGET:	/* Go elsewhere                */

        *redirect = TRUE;	/* Copy port and ip addr       */

        memcpy(Dest_IP, (resp + RFCNB_Pkt_IP_Offset), sizeof(struct in_addr));
        *port = SVAL(resp, RFCNB_Pkt_Port_Offset);

        return (0);
        break;

    default:			/* A protocol error */

        RFCNB_errno = RFCNBE_ProtErr;
        return (RFCNBE_Bad);
        break;
    }
}