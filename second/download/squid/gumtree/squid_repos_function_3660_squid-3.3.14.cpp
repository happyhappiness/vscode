void
Auth::Init()
{
    debugs(29,DBG_IMPORTANT,"Startup: Initializing Authentication Schemes ...");
#if HAVE_AUTH_MODULE_BASIC
    static const char *basic_type = Auth::Basic::Scheme::GetInstance()->type();
    debugs(29,DBG_IMPORTANT,"Startup: Initialized Authentication Scheme '" << basic_type << "'");
#endif
#if HAVE_AUTH_MODULE_DIGEST
    static const char *digest_type = Auth::Digest::Scheme::GetInstance()->type();
    debugs(29,DBG_IMPORTANT,"Startup: Initialized Authentication Scheme '" << digest_type << "'");
#endif
#if HAVE_AUTH_MODULE_NEGOTIATE
    static const char *negotiate_type = Auth::Negotiate::Scheme::GetInstance()->type();
    debugs(29,DBG_IMPORTANT,"Startup: Initialized Authentication Scheme '" << negotiate_type << "'");
#endif
#if HAVE_AUTH_MODULE_NTLM
    static const char *ntlm_type = Auth::Ntlm::Scheme::GetInstance()->type();
    debugs(29,DBG_IMPORTANT,"Startup: Initialized Authentication Scheme '" << ntlm_type << "'");
#endif
    debugs(29,DBG_IMPORTANT,"Startup: Initialized Authentication.");
}