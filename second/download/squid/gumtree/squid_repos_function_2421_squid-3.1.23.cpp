ErrorState *
FwdState::makeConnectingError(const err_type type) const
{
    return errorCon(type, request->flags.need_validation ?
                    HTTP_GATEWAY_TIMEOUT : HTTP_SERVICE_UNAVAILABLE, request);
}