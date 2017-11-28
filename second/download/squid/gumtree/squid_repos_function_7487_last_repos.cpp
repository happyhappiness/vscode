bool
Security::ServerOptions::createStaticServerContext(AnyP::PortCfg &port)
{
    updateTlsVersionLimits();

    Security::ContextPointer t(createBlankContext());
    if (t) {
#if USE_OPENSSL
        if (!Ssl::InitServerContext(t, port))
            return false;
#endif
    }

    staticContext = std::move(t);
    return bool(staticContext);
}