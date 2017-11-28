wordlist *
ACLProtocolData::dump()
{
    wordlist *W = NULL;
    CbDataList<protocol_t> *data = values;

    while (data != NULL) {
        wordlistAdd(&W, ProtocolStr[data->element]);
        data = data->next;
    }

    return W;
}