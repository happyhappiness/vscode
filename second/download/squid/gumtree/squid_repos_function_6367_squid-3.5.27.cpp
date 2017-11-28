void
AIODiskIOStrategy::sync()
{
    assert(aq.aq_state == AQ_STATE_SETUP);

    /*
     * Keep calling callback to complete ops until the queue is empty
     * We can't quit when callback returns 0 - some calls may not
     * return any completed pending events, but they're still pending!
     */

    while (aq.aq_numpending)
        callback();
}