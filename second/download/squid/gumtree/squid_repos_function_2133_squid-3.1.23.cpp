void
ServerStateData::haveParsedReplyHeaders()
{
    Must(theFinalReply);
    maybePurgeOthers();
}