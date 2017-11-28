int
AIODiskIOStrategy::findSlot()
{
    /* Later we should use something a little more .. efficient :) */

    for (int i = 0; i < MAX_ASYNCOP; ++i) {
        if (aq.aq_queue[i].aq_e_state == AQ_ENTRY_FREE)
            /* Found! */
            return i;
    }

    /* found nothing */
    return -1;
}