bool
clientReplyContext::alwaysAllowResponse(http_status sline) const
{
    bool result;

    switch (sline) {

    case HTTP_CONTINUE:

    case HTTP_SWITCHING_PROTOCOLS:

    case HTTP_PROCESSING:

    case HTTP_NO_CONTENT:

    case HTTP_NOT_MODIFIED:
        result = true;
        break;

    default:
        result = false;
    }

    return result;
}