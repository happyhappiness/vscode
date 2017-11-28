ErrorState *
FwdState::makeConnectingError(const err_type type) const
{
    return new ErrorState(type, request->flags.needValidation ?
                          HTTP_GATEWAY_TIMEOUT : HTTP_SERVICE_UNAVAILABLE, request);
}