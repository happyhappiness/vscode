ErrorState *
ErrorState::NewForwarding(err_type type, HttpRequest *request)
{
    assert(request);
    const Http::StatusCode status = request->flags.needValidation ?
                                    Http::scGatewayTimeout : Http::scServiceUnavailable;
    return new ErrorState(type, status, request);
}