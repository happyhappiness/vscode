/* build request prefix and append it to a given MemBuf;
 * return the length of the prefix */
mb_size_t
HttpStateData::buildRequestPrefix(MemBuf * mb)
{
    const int offset = mb->size;
    HttpVersion httpver(1,1);
    const char * url;
    if (_peer && !_peer->options.originserver)
        url = entry->url();
    else
        url = request->urlpath.termedBuf();
    mb->Printf("%s %s %s/%d.%d\r\n",
               RequestMethodStr(request->method),
               url && *url ? url : "/",
               AnyP::ProtocolType_str[httpver.protocol],
