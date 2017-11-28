void
HttpHeader::putAuth(const char *auth_scheme, const char *realm)
{
    assert(auth_scheme && realm);
    httpHeaderPutStrf(this, HDR_WWW_AUTHENTICATE, "%s realm=\"%s\"", auth_scheme, realm);
}