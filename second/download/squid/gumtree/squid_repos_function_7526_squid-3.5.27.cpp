void
RFCNB_Free_Pkt(struct RFCNB_Pkt *pkt)
{
    struct RFCNB_Pkt *pkt_next;
    char *data_ptr;

    while (pkt != NULL) {

        pkt_next = pkt->next;

        data_ptr = pkt->data;

        if (data_ptr != NULL)
            free(data_ptr);

        free(pkt);

        pkt = pkt_next;

    }
}