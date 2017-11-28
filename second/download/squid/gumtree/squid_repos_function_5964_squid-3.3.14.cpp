esiProcessResult_t
esiTry::bestAttemptRV() const
{
    if (flags.attemptfailed)
        return ESI_PROCESS_COMPLETE;
    else
        return ESI_PROCESS_PENDING_MAYFAIL;
}