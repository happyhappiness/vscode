void
AIODiskIOStrategy::init()
{
    /* Make sure the queue isn't setup */
    assert(aq.aq_state == AQ_STATE_NONE);

    /* Loop through, blanking the queue entries */

    /* Done */
    aq.aq_state = AQ_STATE_SETUP;
}