bool
ClientRequestContext::httpStateIsValid()
{
    ClientHttpRequest *http_ = http;

    if (cbdataReferenceValid(http_))
        return true;

    http = NULL;

    cbdataReferenceDone(http_);

    return false;
}