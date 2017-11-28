bool
FwdState::reforwardableStatus(http_status s)
{
    switch (s) {

    case HTTP_BAD_GATEWAY:

    case HTTP_GATEWAY_TIMEOUT:
        return true;

    case HTTP_FORBIDDEN:

    case HTTP_INTERNAL_SERVER_ERROR:

    case HTTP_NOT_IMPLEMENTED:

    case HTTP_SERVICE_UNAVAILABLE:
        return Config.retry.onerror;

    default:
        return false;
    }

    /* NOTREACHED */
}