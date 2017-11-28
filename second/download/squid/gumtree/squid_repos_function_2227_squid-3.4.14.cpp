void
FwdState::sslCrtvdHandleReplyWrapper(void *data, Ssl::CertValidationResponse const &validationResponse)
{
    FwdState * fwd = (FwdState *)(data);
    fwd->sslCrtvdHandleReply(validationResponse);
}