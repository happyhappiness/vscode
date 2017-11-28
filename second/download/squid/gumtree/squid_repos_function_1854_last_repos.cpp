bool
FwdState::reforwardableStatus(const Http::StatusCode s) const
{
    switch (s) {

    case Http::scBadGateway:

    case Http::scGatewayTimeout:
        return true;

    case Http::scForbidden:

    case Http::scInternalServerError:

    case Http::scNotImplemented:

    case Http::scServiceUnavailable:
        return Config.retry.onerror;

    default:
        return false;
    }

    /* NOTREACHED */
}