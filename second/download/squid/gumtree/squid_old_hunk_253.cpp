        return;

    // TODO: bypass if possible

    if (entry->isEmpty()) {
        debugs(11,9, HERE << "creating ICAP error entry after ICAP failure");
        ErrorState *err = errorCon(ERR_ICAP_FAILURE, HTTP_INTERNAL_SERVER_ERROR, request);
        err->xerrno = errno;
        fwd->fail(err);
        fwd->dontRetry(true);
    }

    abortTransaction("ICAP failure");
}

void
ServerStateData::adaptationAclCheckDone(Adaptation::ServiceGroupPointer group)
{
    adaptationAccessCheckPending = false;

    if (abortOnBadEntry("entry went bad while waiting for ICAP ACL check"))
        return;

