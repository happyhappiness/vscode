wordlist *
ACLSslErrorData::dump()
{
    wordlist *W = NULL;
    CbDataList<Ssl::ssl_error_t> *data = values;

    while (data != NULL) {
        wordlistAdd(&W, Ssl::getErrorName(data->element));
        data = data->next;
    }

    return W;
}