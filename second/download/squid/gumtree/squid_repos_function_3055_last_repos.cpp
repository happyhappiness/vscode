void
ConnStateData::sslCrtdHandleReplyWrapper(void *data, const Helper::Reply &reply)
{
    ConnStateData * state_data = (ConnStateData *)(data);
    state_data->sslCrtdHandleReply(reply);
}