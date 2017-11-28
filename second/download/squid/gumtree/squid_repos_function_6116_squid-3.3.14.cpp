esiProcessResult_t
esiSequence::process (int inheritedVarsFlag)
{
    debugs(86, 5, "esiSequence::process: " << this << " processing");

    if (processing) {
        debugs(86, 5, "esiSequence::process: " << this <<
               " reentry attempt during processing");
    }

    /* process as much of the list as we can, stopping only on
     * faliures
     */
    if (!processing || processedcount == 0)
        processingResult = ESI_PROCESS_COMPLETE;

    int dovars = inheritedVarsFlag;

    if (flags.dovars)
        dovars = 1;

    debugs(86, 5, "esiSequence::process: Processing " << this << " with" <<
           (dovars ? "" : "out") << " variable processing");

    processing = true;

    nextElementToProcess(processedcount);

    while (!finishedProcessing()) {
        processStep(dovars);

        if (!processing)
            return processingResult;

        if (processingResult == ESI_PROCESS_FAILED) {
            elements.setNULL (0, elements.size());
            failed = true;
            parent = NULL;
            processing = false;
            return processingResult;
        }
    }

    assert (processingResult != ESI_PROCESS_COMPLETE || processedcount == elements.size());

    if (processingResult == ESI_PROCESS_COMPLETE || processingResult == ESI_PROCESS_PENDING_WONTFAIL)
        wontFail();

    if (processedcount == elements.size() || provideIncrementalData) {
        ESISegment::Pointer temp(new ESISegment);
        render (temp);

        if (temp->next.getRaw() || temp->len)
            parent->provideData(temp, this);
        else
            ESISegmentFreeList (temp);
    }

    /* Depends on full parsing before processing */
    if (processedcount == elements.size())
        parent = NULL;

    debugs(86, 5, "esiSequence::process: " << this << " completed");

    processing = false;

    return processingResult;
}