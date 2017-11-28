esiProcessResult_t
ESIContext::process ()
{
    /* parsing:
     * read through buffered, skipping plain text, and skipping any
     * <...> entry that is not an <esi: entry.
     * when it's found, hand an esiLiteral of the preceding data to our current
     * context
     */

    if (parserState.parsing) {
        /* in middle of parsing - finish here */
        return ESI_PROCESS_PENDING_MAYFAIL;
    }

    assert (flags.finished == 0);

    assert (!flags.error);

    if (!hasCachedAST())
        parse();
    else if (!flags.finishedtemplate)
        getCachedAST();

    if (flags.error) {
        debugs(86, 5, "ESIContext::process: Parsing failed");
        finishChildren ();
        parserState.popAll();
        return ESI_PROCESS_FAILED;
    }

    if (!flags.finishedtemplate && !incoming.getRaw() && !cachedASTInUse) {
        buffered = new ESISegment;
        incoming = buffered;
    }

    if (!flags.finishedtemplate && !cachedASTInUse) {
        return ESI_PROCESS_PENDING_MAYFAIL;
    }

    assert (flags.finishedtemplate || cachedASTInUse);
    updateCachedAST();
    /* ok, we've done all we can with the data. What can we process now?
     */
    {
        esiProcessResult_t status;
        PROF_start(esiProcessing);
        processing = true;
        status = tree->process(0);
        processing = false;

        switch (status) {

        case ESI_PROCESS_COMPLETE:
            debugs(86, 5, "esiProcess: tree Processed OK");
            break;

        case ESI_PROCESS_PENDING_WONTFAIL:
            debugs(86, 5, "esiProcess: tree Processed PENDING OK");
            break;

        case ESI_PROCESS_PENDING_MAYFAIL:
            debugs(86, 5, "esiProcess: tree Processed PENDING UNKNOWN");
            break;

        case ESI_PROCESS_FAILED:
            debugs(86, DBG_CRITICAL, "esiProcess: tree Processed FAILED");
            setError();

            setErrorMessage("esiProcess: ESI template Processing failed.");

            PROF_stop(esiProcessing);

            return ESI_PROCESS_FAILED;

            break;
        }

        if (status != ESI_PROCESS_PENDING_MAYFAIL && (flags.finishedtemplate || cachedASTInUse)) {
            /* We've read the entire template, and no nodes will
             * return failure
             */
            debugs(86, 5, "esiProcess, request will succeed");
            flags.oktosend = 1;
        }

        if (status == ESI_PROCESS_COMPLETE
                && (flags.finishedtemplate || cachedASTInUse)) {
            /* we've finished all processing. Render and send. */
            debugs(86, 5, "esiProcess, processing complete");
            flags.finished = 1;
        }

        PROF_stop(esiProcessing);
        return status; /* because we have no callbacks */
    }
}