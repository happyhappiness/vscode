wordlist *
ACLMethodData::dump()
{
    wordlist *W = NULL;
    CbDataList<HttpRequestMethod> *data = values;

    while (data != NULL) {
        wordlistAdd(&W, RequestMethodStr(data->element));
        data = data->next;
    }

    return W;
}