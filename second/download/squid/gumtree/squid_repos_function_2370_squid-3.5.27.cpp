ErrorState *
FwdState::makeConnectingError(const err_type type) const
{
    return new ErrorState(type, request->flags.needValidation ?
                          Http::scGatewayTimeout : Http::scServiceUnavailable, request);
}