static int
esiAlwaysPassthrough(Http::StatusCode sline)
{
    int result;

    switch (sline) {

    case Http::scContinue: /* Should never reach us... but squid needs to alter to accomodate this */

    case Http::scSwitchingProtocols: /* Ditto */

    case Http::scProcessing: /* Unknown - some extension */

    case Http::scNoContent: /* no body, no esi */

    case Http::scNotModified: /* ESI does not affect assembled page headers, so 304s are valid */
        result = 1;
        /* unreached */
        break;

    default:
        result = 0;
    }

    return result;
}