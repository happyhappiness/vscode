bool
ServerStateData::getMoreRequestBody(MemBuf &buf)
{
    // default implementation does not encode request body content
    Must(requestBodySource != NULL);
    return requestBodySource->getMoreData(buf);
}