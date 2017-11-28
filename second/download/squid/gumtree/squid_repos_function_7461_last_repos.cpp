static
Security::Extensions
Security::SupportedExtensions()
{
#if USE_OPENSSL

    // optimize lookup speed by reserving the number of values x3, approximately
    Security::Extensions extensions(64);

    // Keep this list ordered and up to date by running something like
    // egrep '# *define TLSEXT_TYPE_' /usr/include/openssl/tls1.h
    // TODO: Teach OpenSSL to return the list of extensions it supports.
#if defined(TLSEXT_TYPE_server_name) // 0
    extensions.insert(TLSEXT_TYPE_server_name);
#endif
#if defined(TLSEXT_TYPE_max_fragment_length) // 1
    extensions.insert(TLSEXT_TYPE_max_fragment_length);
#endif
#if defined(TLSEXT_TYPE_client_certificate_url) // 2
    extensions.insert(TLSEXT_TYPE_client_certificate_url);
#endif
#if defined(TLSEXT_TYPE_trusted_ca_keys) // 3
    extensions.insert(TLSEXT_TYPE_trusted_ca_keys);
#endif
#if defined(TLSEXT_TYPE_truncated_hmac) // 4
    extensions.insert(TLSEXT_TYPE_truncated_hmac);
#endif
#if defined(TLSEXT_TYPE_status_request) // 5
    extensions.insert(TLSEXT_TYPE_status_request);
#endif
#if defined(TLSEXT_TYPE_user_mapping) // 6
    extensions.insert(TLSEXT_TYPE_user_mapping);
#endif
#if defined(TLSEXT_TYPE_client_authz) // 7
    extensions.insert(TLSEXT_TYPE_client_authz);
#endif
#if defined(TLSEXT_TYPE_server_authz) // 8
    extensions.insert(TLSEXT_TYPE_server_authz);
#endif
#if defined(TLSEXT_TYPE_cert_type) // 9
    extensions.insert(TLSEXT_TYPE_cert_type);
#endif
#if defined(TLSEXT_TYPE_elliptic_curves) // 10
    extensions.insert(TLSEXT_TYPE_elliptic_curves);
#endif
#if defined(TLSEXT_TYPE_ec_point_formats) // 11
    extensions.insert(TLSEXT_TYPE_ec_point_formats);
#endif
#if defined(TLSEXT_TYPE_srp) // 12
    extensions.insert(TLSEXT_TYPE_srp);
#endif
#if defined(TLSEXT_TYPE_signature_algorithms) // 13
    extensions.insert(TLSEXT_TYPE_signature_algorithms);
#endif
#if defined(TLSEXT_TYPE_use_srtp) // 14
    extensions.insert(TLSEXT_TYPE_use_srtp);
#endif
#if defined(TLSEXT_TYPE_heartbeat) // 15
    extensions.insert(TLSEXT_TYPE_heartbeat);
#endif
#if defined(TLSEXT_TYPE_session_ticket) // 35
    extensions.insert(TLSEXT_TYPE_session_ticket);
#endif
#if defined(TLSEXT_TYPE_renegotiate) // 0xff01
    extensions.insert(TLSEXT_TYPE_renegotiate);
#endif
#if defined(TLSEXT_TYPE_next_proto_neg) // 13172
    extensions.insert(TLSEXT_TYPE_next_proto_neg);
#endif

    /*
     * OpenSSL does not support these last extensions by default, but those
     * building the OpenSSL libraries and/or Squid might define them.
     */

    // OpenSSL may be built to support draft-rescorla-tls-opaque-prf-input-00,
    // with the extension type value configured at build time. OpenSSL, Squid,
    // and TLS agents must all be built with the same extension type value.
#if defined(TLSEXT_TYPE_opaque_prf_input)
    extensions.insert(TLSEXT_TYPE_opaque_prf_input);
#endif

    // Define this to add extensions supported by your OpenSSL but unknown to
    // your Squid version. Use {list-initialization} to add multiple extensions.
#if defined(TLSEXT_TYPE_SUPPORTED_BY_MY_SQUID)
    extensions.insert(TLSEXT_TYPE_SUPPORTED_BY_MY_SQUID);
#endif

    return extensions; // might be empty
#else

    return Extensions(); // no extensions are supported without OpenSSL
#endif
}