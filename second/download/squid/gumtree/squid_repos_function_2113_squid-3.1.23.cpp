HttpReply *
ServerStateData::setFinalReply(HttpReply *rep)
{
    debugs(11,5, HERE << this << " setting final reply to " << rep);

    assert(!theFinalReply);
    assert(rep);
    theFinalReply = HTTPMSGLOCK(rep);

    entry->replaceHttpReply(theFinalReply);
    haveParsedReplyHeaders();

    return theFinalReply;
}