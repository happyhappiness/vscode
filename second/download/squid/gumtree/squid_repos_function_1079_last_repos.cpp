void
Acl::Init()
{
    /* the registration order does not matter */

    // The explicit return type (ACL*) for lambdas is needed because the type
    // of the return expression inside lambda is not ACL* but AclFoo* while
    // Acl::Maker is defined to return ACL*.

    RegisterMaker("all-of", [](TypeName)->ACL* { return new Acl::AllOf; }); // XXX: Add name parameter to ctor
    RegisterMaker("any-of", [](TypeName)->ACL* { return new Acl::AnyOf; }); // XXX: Add name parameter to ctor
    RegisterMaker("random", [](TypeName name)->ACL* { return new ACLRandom(name); });
    RegisterMaker("time", [](TypeName name)->ACL* { return new ACLStrategised<time_t>(new ACLTimeData, new ACLTimeStrategy, name); });
    RegisterMaker("src_as", [](TypeName name)->ACL* { return new ACLStrategised<Ip::Address>(new ACLASN, new ACLSourceASNStrategy, name); });
    RegisterMaker("dst_as", [](TypeName name)->ACL* { return new ACLStrategised<Ip::Address>(new ACLASN, new ACLDestinationASNStrategy, name); });
    RegisterMaker("browser", [](TypeName name)->ACL* { return new ACLStrategised<char const *>(new ACLRegexData, new ACLRequestHeaderStrategy<Http::HdrType::USER_AGENT>, name); });
    RegisterMaker("dstdomain", [](TypeName name)->ACL* { return new ACLStrategised<char const *>(new ACLDomainData, new ACLDestinationDomainStrategy, name); });
    RegisterMaker("dstdom_regex", [](TypeName name)->ACL* { return new ACLStrategised<char const *>(new ACLRegexData, new ACLDestinationDomainStrategy , name); });
    RegisterMaker("dst", [](TypeName)->ACL* { return new ACLDestinationIP; }); // XXX: Add name parameter to ctor
    RegisterMaker("hier_code", [](TypeName name)->ACL* { return new ACLStrategised<hier_code>(new ACLHierCodeData, new ACLHierCodeStrategy, name); });
    RegisterMaker("rep_header", [](TypeName name)->ACL* { return new ACLStrategised<HttpHeader*>(new ACLHTTPHeaderData, new ACLHTTPRepHeaderStrategy, name); });
    RegisterMaker("req_header", [](TypeName name)->ACL* { return new ACLStrategised<HttpHeader*>(new ACLHTTPHeaderData, new ACLHTTPReqHeaderStrategy, name); });
    RegisterMaker("http_status", [](TypeName name)->ACL* { return new ACLHTTPStatus(name); });
    RegisterMaker("maxconn", [](TypeName name)->ACL* { return new ACLMaxConnection(name); });
    RegisterMaker("method", [](TypeName name)->ACL* { return new ACLStrategised<HttpRequestMethod>(new ACLMethodData, new ACLMethodStrategy, name); });
    RegisterMaker("localip", [](TypeName)->ACL* { return new ACLLocalIP; }); // XXX: Add name parameter to ctor
    RegisterMaker("localport", [](TypeName name)->ACL* { return new ACLStrategised<int>(new ACLIntRange, new ACLLocalPortStrategy, name); });
    RegisterMaker("myportname", [](TypeName name)->ACL* { return new ACLStrategised<const char *>(new ACLStringData, new ACLMyPortNameStrategy, name); });
    RegisterMaker("peername", [](TypeName name)->ACL* { return new ACLStrategised<const char *>(new ACLStringData, new ACLPeerNameStrategy, name); });
    RegisterMaker("peername_regex", [](TypeName name)->ACL* { return new ACLStrategised<char const *>(new ACLRegexData, new ACLPeerNameStrategy, name); });
    RegisterMaker("proto", [](TypeName name)->ACL* { return new ACLStrategised<AnyP::ProtocolType>(new ACLProtocolData, new ACLProtocolStrategy, name); });
    RegisterMaker("referer_regex", [](TypeName name)->ACL* { return new ACLStrategised<char const *>(new ACLRegexData, new ACLRequestHeaderStrategy<Http::HdrType::REFERER>, name); });
    RegisterMaker("rep_mime_type", [](TypeName name)->ACL* { return new ACLStrategised<char const *>(new ACLRegexData, new ACLReplyHeaderStrategy<Http::HdrType::CONTENT_TYPE>, name); });
    RegisterMaker("req_mime_type", [](TypeName name)->ACL* { return new ACLStrategised<char const *>(new ACLRegexData, new ACLRequestHeaderStrategy<Http::HdrType::CONTENT_TYPE>, name); });
    RegisterMaker("srcdomain", [](TypeName name)->ACL* { return new ACLStrategised<char const *>(new ACLDomainData, new ACLSourceDomainStrategy, name); });
    RegisterMaker("srcdom_regex", [](TypeName name)->ACL* { return new ACLStrategised<char const *>(new ACLRegexData, new ACLSourceDomainStrategy, name); });
    RegisterMaker("src", [](TypeName)->ACL* { return new ACLSourceIP; }); // XXX: Add name parameter to ctor
    RegisterMaker("url_regex", [](TypeName name)->ACL* { return new ACLStrategised<char const *>(new ACLRegexData, new ACLUrlStrategy, name); });
    RegisterMaker("urllogin", [](TypeName name)->ACL* { return new ACLStrategised<char const *>(new ACLRegexData, new ACLUrlLoginStrategy, name); });
    RegisterMaker("urlpath_regex", [](TypeName name)->ACL* { return new ACLStrategised<char const *>(new ACLRegexData, new ACLUrlPathStrategy, name); });
    RegisterMaker("port", [](TypeName name)->ACL* { return new ACLStrategised<int>(new ACLIntRange, new ACLUrlPortStrategy, name); });
    RegisterMaker("external", [](TypeName name)->ACL* { return new ACLExternal(name); });
    RegisterMaker("squid_error", [](TypeName name)->ACL* { return new ACLStrategised<err_type>(new ACLSquidErrorData, new ACLSquidErrorStrategy, name); });
    RegisterMaker("connections_encrypted", [](TypeName name)->ACL* { return new Acl::ConnectionsEncrypted(name); });
    RegisterMaker("tag", [](TypeName name)->ACL* { return new ACLStrategised<const char *>(new ACLStringData, new ACLTagStrategy, name); });
    RegisterMaker("note", [](TypeName name)->ACL* { return new ACLStrategised<NotePairs::Entry*>(new ACLNoteData, new ACLNoteStrategy, name); });
    RegisterMaker("has", [](TypeName name)->ACL* {return new ACLStrategised<ACLChecklist *>(new ACLHasComponentData, new ACLHasComponentStrategy, name); });
    RegisterMaker("transaction_initiator", [](TypeName name)->ACL* {return new Acl::TransactionInitiator(name);});

#if USE_OPENSSL
    RegisterMaker("ssl_error", [](TypeName name)->ACL* { return new ACLStrategised<const Security::CertErrors *>(new ACLSslErrorData, new ACLSslErrorStrategy, name); });
    RegisterMaker("user_cert", [](TypeName name)->ACL* { return new ACLStrategised<X509*>(new ACLCertificateData(Ssl::GetX509UserAttribute, "*"), new ACLCertificateStrategy, name); });
    RegisterMaker("ca_cert", [](TypeName name)->ACL* { return new ACLStrategised<X509*>(new ACLCertificateData(Ssl::GetX509CAAttribute, "*"), new ACLCertificateStrategy, name); });
    RegisterMaker("server_cert_fingerprint", [](TypeName name)->ACL* { return new ACLStrategised<X509*>(new ACLCertificateData(Ssl::GetX509Fingerprint, "-sha1", true), new ACLServerCertificateStrategy, name); });
    RegisterMaker("at_step", [](TypeName name)->ACL* { return new ACLStrategised<Ssl::BumpStep>(new ACLAtStepData, new ACLAtStepStrategy, name); });
    RegisterMaker("ssl::server_name", [](TypeName name)->ACL* { return new ACLStrategised<char const *>(new ACLServerNameData, new ACLServerNameStrategy, name); });
    RegisterMaker("ssl::server_name_regex", [](TypeName name)->ACL* { return new ACLStrategised<char const *>(new ACLRegexData, new ACLServerNameStrategy, name); });
#endif

#if USE_SQUID_EUI
    RegisterMaker("arp", [](TypeName name)->ACL* { return new ACLARP(name); });
    RegisterMaker("eui64", [](TypeName name)->ACL* { return new ACLEui64(name); });
#endif

#if USE_IDENT
    RegisterMaker("ident", [](TypeName name)->ACL* { return new ACLIdent(new ACLUserData, name); });
    RegisterMaker("ident_regex", [](TypeName name)->ACL* { return new ACLIdent(new ACLRegexData, name); });
#endif

#if USE_AUTH
    RegisterMaker("ext_user", [](TypeName name)->ACL* { return new ACLExtUser(new ACLUserData, name); });
    RegisterMaker("ext_user_regex", [](TypeName name)->ACL* { return new ACLExtUser(new ACLRegexData, name); });
    RegisterMaker("proxy_auth", [](TypeName name)->ACL* { return new ACLProxyAuth(new ACLUserData, name); });
    RegisterMaker("proxy_auth_regex", [](TypeName name)->ACL* { return new ACLProxyAuth(new ACLRegexData, name); });
    RegisterMaker("max_user_ip", [](TypeName name)->ACL* { return new ACLMaxUserIP(name); });
#endif

#if USE_ADAPTATION
    RegisterMaker("adaptation_service", [](TypeName name)->ACL* { return new ACLStrategised<const char *>(new ACLAdaptationServiceData, new ACLAdaptationServiceStrategy, name); });
#endif

#if SQUID_SNMP
    RegisterMaker("snmp_community", [](TypeName name)->ACL* { return new ACLStrategised<const char *>(new ACLStringData, new ACLSNMPCommunityStrategy, name); });
#endif
}