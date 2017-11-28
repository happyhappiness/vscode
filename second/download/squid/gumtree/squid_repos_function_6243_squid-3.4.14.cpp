void
Format::Token::Init()
{
    // TODO standard log tokens
    // TODO external ACL fmt tokens

#if USE_ADAPTATION
    TheConfig.registerTokens(String("adapt"),::Format::TokenTableAdapt);
#endif
#if ICAP_CLIENT
    TheConfig.registerTokens(String("icap"),::Format::TokenTableIcap);
#endif
#if USE_SSL
    TheConfig.registerTokens(String("ssl"),::Format::TokenTableSsl);
#endif
}