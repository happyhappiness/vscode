void
AuthScheme::FreeAll()
{
    while (GetSchemes().size()) {
        AuthScheme *scheme = GetSchemes().back();
        GetSchemes().pop_back();
        scheme->done();
    }
}