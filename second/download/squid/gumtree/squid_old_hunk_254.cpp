        return;
    }

    startAdaptation(group, originalRequest());
    processReplyBody();
}

void
ServerStateData::adaptationAclCheckDoneWrapper(Adaptation::ServiceGroupPointer group, void *data)
{
    ServerStateData *state = (ServerStateData *)data;
    state->adaptationAclCheckDone(group);
}
#endif

void
ServerStateData::sendBodyIsTooLargeError()
{
    ErrorState *err = errorCon(ERR_TOO_BIG, HTTP_FORBIDDEN, request);
    err->xerrno = errno;
    fwd->fail(err);
    fwd->dontRetry(true);
    abortTransaction("Virgin body too large.");
}

