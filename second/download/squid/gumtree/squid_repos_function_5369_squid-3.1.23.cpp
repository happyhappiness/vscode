esiProcessResult_t
esiTry::process (int dovars)
{
    esiProcessResult_t rv = ESI_PROCESS_PENDING_MAYFAIL;
    assert (this);

    if (!attempt.getRaw()) {
        debugs(86, 0, "esiTryProcess: Try has no attempt element - ESI template is invalid (section 3.4)");
        return ESI_PROCESS_FAILED;
    }

    if (!except.getRaw()) {
        debugs(86, 0, "esiTryProcess: Try has no except element - ESI template is invalid (section 3.4)");
        return ESI_PROCESS_FAILED;
    }

    if (!flags.attemptfailed)
        /* Try the attempt branch */
        switch ((rv = attempt->process(dovars))) {

        case ESI_PROCESS_COMPLETE:
            debugs(86, 5, "esiTryProcess: attempt Processed OK");
            flags.attemptok = 1;
            return ESI_PROCESS_COMPLETE;

        case ESI_PROCESS_PENDING_WONTFAIL:
            debugs(86, 5, "esiTryProcess: attempt Processed PENDING OK");
            /* We're not done yet, but don't need to test except */
            return ESI_PROCESS_PENDING_WONTFAIL;

        case ESI_PROCESS_PENDING_MAYFAIL:
            debugs(86, 5, "eseSequenceProcess: element Processed PENDING UNKNOWN");
            break;

        case ESI_PROCESS_FAILED:
            debugs(86, 5, "esiSequenceProcess: element Processed FAILED");
            flags.attemptfailed = 1;
            break;
        }

    /* attempt is either MAYFAIL or FAILED */
    if (flags.exceptok)
        return bestAttemptRV();

    /* query except to see if it has a definite result */
    if (!flags.exceptfailed)
        /* Try the except branch */
        switch (except->process(dovars)) {

        case ESI_PROCESS_COMPLETE:
            debugs(86, 5, "esiTryProcess: except Processed OK");
            flags.exceptok = 1;
            return bestAttemptRV();

        case ESI_PROCESS_PENDING_WONTFAIL:
            debugs(86, 5, "esiTryProcess: attempt Processed PENDING OK");
            /* We're not done yet, but can't fail */
            return ESI_PROCESS_PENDING_WONTFAIL;

        case ESI_PROCESS_PENDING_MAYFAIL:
            debugs(86, 5, "eseSequenceProcess: element Processed PENDING UNKNOWN");
            /* The except branch fail fail */
            return ESI_PROCESS_PENDING_MAYFAIL;

        case ESI_PROCESS_FAILED:
            debugs(86, 5, "esiSequenceProcess: element Processed FAILED");
            flags.exceptfailed = 1;
            break;
        }

    if (flags.exceptfailed && flags.attemptfailed)
        return ESI_PROCESS_FAILED;

    /* one of attempt or except returned PENDING MAYFAIL */
    return ESI_PROCESS_PENDING_MAYFAIL;
}