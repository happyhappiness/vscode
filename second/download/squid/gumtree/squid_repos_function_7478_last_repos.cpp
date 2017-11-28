static AnyP::ProtocolVersion
toProtocolVersion(const int v)
{
    switch(v) {
#if defined(TLS1_2_VERSION)
    case TLS1_2_VERSION:
        return AnyP::ProtocolVersion(AnyP::PROTO_TLS, 1, 2);
#endif
#if defined(TLS1_1_VERSION)
    case TLS1_1_VERSION:
        return AnyP::ProtocolVersion(AnyP::PROTO_TLS, 1, 1);
#endif
#if defined(TLS1_VERSION)
    case TLS1_VERSION:
        return AnyP::ProtocolVersion(AnyP::PROTO_TLS, 1, 0);
#endif
#if defined(SSL3_VERSION)
    case SSL3_VERSION:
        return AnyP::ProtocolVersion(AnyP::PROTO_SSL, 3, 0);
#endif
#if defined(SSL2_VERSION)
    case SSL2_VERSION:
        return AnyP::ProtocolVersion(AnyP::PROTO_SSL, 2, 0);
#endif
    default:
        return AnyP::ProtocolVersion();
    }
}