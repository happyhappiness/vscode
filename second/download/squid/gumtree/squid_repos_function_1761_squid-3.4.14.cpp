static int
peerDigestFetchedEnough(DigestFetchState * fetch, char *buf, ssize_t size, const char *step_name)
{
    PeerDigest *pd = NULL;
    const char *host = "<unknown>";	/* peer host */
    const char *reason = NULL;	/* reason for completion */
    const char *no_bug = NULL;	/* successful completion if set */
    const int pdcb_valid = cbdataReferenceValid(fetch->pd);
    const int pcb_valid = cbdataReferenceValid(fetch->pd->peer);

    /* test possible exiting conditions (the same for most steps!)
     * cases marked with '?!' should not happen */

    if (!reason) {
        if (!(pd = fetch->pd))
            reason = "peer digest disappeared?!";

#if DONT			/* WHY NOT? /HNO */

        else if (!cbdataReferenceValid(pd))
            reason = "invalidated peer digest?!";

#endif

        else
            host = pd->host.termedBuf();
    }

    debugs(72, 6, step_name << ": peer " << host << ", offset: " <<
           fetch->offset << " size: " << size << ".");

    /* continue checking (with pd and host known and valid) */

    if (!reason) {
        if (!cbdataReferenceValid(pd->peer))
            reason = "peer disappeared";
        else if (size < 0)
            reason = "swap failure";
        else if (!fetch->entry)
            reason = "swap aborted?!";
        else if (EBIT_TEST(fetch->entry->flags, ENTRY_ABORTED))
            reason = "swap aborted";
    }

    /* continue checking (maybe-successful eof case) */
    if (!reason && !size) {
        if (!pd->cd)
            reason = "null digest?!";
        else if (fetch->mask_offset != (int)pd->cd->mask_size)
            reason = "premature end of digest?!";
        else if (!peerDigestUseful(pd))
            reason = "useless digest";
        else
            reason = no_bug = "success";
    }

    /* finish if we have a reason */
    if (reason) {
        const int level = strstr(reason, "?!") ? 1 : 3;
        debugs(72, level, "" << step_name << ": peer " << host << ", exiting after '" << reason << "'");
        peerDigestReqFinish(fetch, buf,
                            1, pdcb_valid, pcb_valid, reason, !no_bug);
    } else {
        /* paranoid check */
        assert(pdcb_valid && pcb_valid);
    }

    return reason != NULL;
}