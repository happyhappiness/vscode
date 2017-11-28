void
HttpHeader::putAuth(const char *auth_scheme, const char *realm)
{
    assert(auth_scheme && realm);
    httpHeaderPutStrf(this, Http::HdrType::WWW_AUTHENTICATE, "%s realm=\"%s\"", auth_scheme, realm);
}