wordlist *
ACLProtocolData::dump()
{
    wordlist *W = NULL;
    CbDataList<AnyP::ProtocolType> *data = values;

    while (data != NULL) {
        wordlistAdd(&W, AnyP::ProtocolType_str[data->element]);
        data = data->next;
    }

    return W;
}