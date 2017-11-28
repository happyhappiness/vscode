esiProcessResult_t
esiSequence::processOne(int dovars, size_t index)
{
    debugs (86,5, "esiSequence::process " << this << " about to process element[" << index << "] " << elements[index].getRaw());

    switch (elements[index]->process(dovars)) {

    case ESI_PROCESS_COMPLETE:
        debugs(86, 5, "esiSequenceProcess: " << this << " element " << elements[index].getRaw() << " Processed OK");

        if (index == processedcount)
            /* another completely ready */
            ++processedcount;

        return ESI_PROCESS_COMPLETE;

    case ESI_PROCESS_PENDING_WONTFAIL:
        debugs(86, 5, "esiSequenceProcess: element Processed PENDING OK");

        return ESI_PROCESS_PENDING_WONTFAIL;

    case ESI_PROCESS_PENDING_MAYFAIL:
        debugs(86, 5, "eseSequenceProcess: element Processed PENDING UNKNOWN");

        return ESI_PROCESS_PENDING_MAYFAIL;

    case ESI_PROCESS_FAILED:
        debugs(86, 5, "esiSequenceProcess: element Processed FAILED");

        return ESI_PROCESS_FAILED;

    default:
        fatal ("unexpected code in esiSequence::processOne\n");

        return ESI_PROCESS_FAILED;
    }
}