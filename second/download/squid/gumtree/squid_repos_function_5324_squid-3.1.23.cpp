static int
esiAlwaysPassthrough(http_status sline)
{
    int result;

    switch (sline) {

    case HTTP_CONTINUE: /* Should never reach us... but squid needs to alter to accomodate this */

    case HTTP_SWITCHING_PROTOCOLS: /* Ditto */

    case HTTP_PROCESSING: /* Unknown - some extension */

    case HTTP_NO_CONTENT: /* no body, no esi */

    case HTTP_NOT_MODIFIED: /* ESI does not affect assembled page headers, so 304s are valid */
        result = 1;
        /* unreached */
        break;

    default:
        result = 0;
    }

    return result;
}