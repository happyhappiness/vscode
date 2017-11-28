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

    debugs(93,9, HERE << info.icapReply->sline.status);
    if (!info.icapReply->sline.status) // failed to parse the reply; I/O err
        return true;

    ACLFilledChecklist *cl =
        new ACLFilledChecklist(TheConfig.repeat, info.icapRequest, dash_str);
    cl->reply = HTTPMSGLOCK(info.icapReply);

    bool result = cl->fastCheck() == ACCESS_ALLOWED;
    delete cl;
    return result;
}