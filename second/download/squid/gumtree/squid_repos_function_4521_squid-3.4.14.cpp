wordlist *
ACLSslErrorData::dump()
{
    wordlist *W = NULL;
    Ssl::Errors *data = values;

    while (data != NULL) {
        wordlistAdd(&W, Ssl::GetErrorName(data->element));
        data = data->next;
    }

    return W;
}