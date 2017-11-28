bool
clientReplyContext::alwaysAllowResponse(Http::StatusCode sline) const
{
    bool result;

    switch (sline) {

    case Http::scContinue:

    case Http::scSwitchingProtocols:

    case Http::scProcessing:

    case Http::scNoContent:

    case Http::scNotModified:
        result = true;
        break;

    default:
        result = false;
    }

    return result;
}