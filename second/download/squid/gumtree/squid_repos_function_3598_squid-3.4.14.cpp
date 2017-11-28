void
ConnStateData::sslCrtdHandleReplyWrapper(void *data, const HelperReply &reply)
{
    ConnStateData * state_data = (ConnStateData *)(data);
    state_data->sslCrtdHandleReply(reply);
}