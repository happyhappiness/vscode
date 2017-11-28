void
ESIInclude::Start (ESIStreamContext::Pointer stream, char const *url, ESIVarState *vars)
{
    if (!stream.getRaw())
        return;

    HttpHeader tempheaders(hoRequest);

    prepareRequestHeaders(tempheaders, vars);

    /* Ensure variable state is clean */
    vars->feedData(url, strlen (url));

    /* tempUrl is eaten by the request */
    char const *tempUrl = vars->extractChar ();

    debugs(86, 5, "ESIIncludeStart: Starting subrequest with url '" << tempUrl <<
           "'");

    if (clientBeginRequest(METHOD_GET, tempUrl, esiBufferRecipient, esiBufferDetach, stream.getRaw(), &tempheaders, stream->localbuffer->buf, HTTP_REQBUF_SZ)) {
        debugs(86, DBG_CRITICAL, "starting new ESI subrequest failed");
    }

    tempheaders.clean();
}