bool Adaptation::Icap::Launcher::canRepeat(Adaptation::Icap::XactAbortInfo &info) const
{
    debugs(93,9, HERE << shutting_down);
    if (theLaunches >= TheConfig.repeat_limit || shutting_down)
        return false;

    debugs(93,9, HERE << info.isRepeatable); // TODO: update and use status()
    if (!info.isRepeatable)
        return false;

    debugs(93,9, HERE << info.icapReply);
    if (!info.icapReply) // did not get to read an ICAP reply; a timeout?
        return true;

    debugs(93,9, info.icapReply->sline.status());
    // XXX: Http::scNone is not the only sign of parse error
    // XXX: if there is a specific HTTP error code describing the problem, that may be set
    if (info.icapReply->sline.status() == Http::scNone) // failed to parse the reply; I/O err
        return true;

    ACLFilledChecklist *cl =
        new ACLFilledChecklist(TheConfig.repeat, info.icapRequest, dash_str);
    cl->reply = info.icapReply;
    HTTPMSGLOCK(cl->reply);

    bool result = cl->fastCheck().allowed();
    delete cl;
    return result;
}