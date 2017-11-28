void
Format::Token::Init()
{
    // TODO standard log tokens

#if USE_ADAPTATION
    TheConfig.registerTokens(String("adapt"),::Format::TokenTableAdapt);
#endif
#if ICAP_CLIENT
    TheConfig.registerTokens(String("icap"),::Format::TokenTableIcap);
#endif
#if USE_OPENSSL
    TheConfig.registerTokens(String("tls"),::Format::TokenTableSsl);
    TheConfig.registerTokens(String("ssl"),::Format::TokenTableSsl);
#endif
}