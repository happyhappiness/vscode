esiProcessResult_t
ESIInclude::process (int dovars)
{
    /* Prevent refcount race leading to free */
    Pointer me (this);
    start();
    debugs(86, 5, "ESIIncludeRender: Processing include " << this);

    if (flags.failed) {
        if (flags.onerrorcontinue)
            return ESI_PROCESS_COMPLETE;
        else
            return ESI_PROCESS_FAILED;
    }

    if (!flags.finished) {
        if (flags.onerrorcontinue)
            return ESI_PROCESS_PENDING_WONTFAIL;
        else
            return ESI_PROCESS_PENDING_MAYFAIL;
    }

    return ESI_PROCESS_COMPLETE;
}