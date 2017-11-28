esiKick_t
ESIContext::kick ()
{
    assert (this);

    if (flags.kicked) {
        debugs(86, 5, "esiKick: Re-entered whilst in progress");
        // return ESI_KICK_INPROGRESS;
    } else
        ++flags.kicked;

    if (flags.detached)
        /* we've been detached from - we can't do anything more */
        return ESI_KICK_FAILED;

    /* Something has occured. Process any remaining nodes */
    if (!flags.finished)
        /* Process some of our data */
        switch (process ()) {

        case ESI_PROCESS_COMPLETE:
            debugs(86, 5, "esiKick: esiProcess OK");
            break;

        case ESI_PROCESS_PENDING_WONTFAIL:
            debugs(86, 5, "esiKick: esiProcess PENDING OK");
            break;

        case ESI_PROCESS_PENDING_MAYFAIL:
            debugs(86, 5, "esiKick: esiProcess PENDING UNKNOWN");
            break;

        case ESI_PROCESS_FAILED:
            debugs(86, 2, "esiKick: esiProcess " << this << " FAILED");
            /* this can not happen - processing can't fail until we have data,
             * and when we come here we have sent data to the client
             */

            if (pos == 0)
                fail ();

            --flags.kicked;

            return ESI_KICK_FAILED;
        }

    /* Render if we can to get maximal sent data */
    assert (tree.getRaw() || flags.error);

    if (!flags.finished && !outbound.getRaw()) {
        outboundtail = new ESISegment;
        outbound = outboundtail;
    }

    if (!flags.error && !flags.finished)
        tree->render(outboundtail);

    if (!flags.finished)
        fixupOutboundTail();

    /* Is there data to send? */
    if (send ()) {
        /* some data was sent. we're finished until the next read */
        --flags.kicked;
        return ESI_KICK_SENT;
    }

    --flags.kicked;
    /* nothing to send */
    return flags.error ? ESI_KICK_FAILED : ESI_KICK_PENDING;
}