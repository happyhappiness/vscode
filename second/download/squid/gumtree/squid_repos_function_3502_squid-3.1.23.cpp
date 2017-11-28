void
ConnStateData::sslCrtdHandleReplyWrapper(void *data, char *reply)
{
    ConnStateData * state_data = (ConnStateData *)(data);
    state_data->sslCrtdHandleReply(reply);
}