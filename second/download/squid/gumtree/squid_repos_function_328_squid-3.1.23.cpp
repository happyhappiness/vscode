void
RFCNB_Free_Pkt(struct RFCNB_Pkt *pkt)
{
    struct RFCNB_Pkt *pkt_next;

    while (pkt != NULL) {

        pkt_next = pkt->next;

        if (pkt->data != NULL)
            free(pkt->data);

        free(pkt);

        pkt = pkt_next;

    }

}