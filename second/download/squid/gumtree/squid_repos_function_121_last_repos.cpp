void
Transport::TheConfig::usage()
{
    std::cerr << "Connection Settings" << std::endl
              << "  -h | --host host     Send message to server on 'host'.  Default is localhost." << std::endl
              << "  -l | --local host    Specify a local IP address to bind to.  Default is none." << std::endl
              << "  -p | --port port     Port number on server to contact. Default is " << CACHE_HTTP_PORT << "." << std::endl
              << "  -T timeout           Timeout in seconds for read/write operations" << std::endl
#if USE_GNUTLS
              << "  --https              Use TLS/SSL on the HTTP connection" << std::endl
              << std::endl
              << "  TLS options:" << std::endl
              << "    --anonymous-tls    Use Anonymous TLS. Sets default parameters:" << std::endl
              << "                         \"PERFORMANCE:+ANON-ECDH:+ANON-DH\"" << std::endl
              << "    --params=\"...\"   Use the given parameters." << std::endl
              << "    --cert=FILE        Path to a PEM file holding the client X.509 certificate chain." << std::endl
              << "                       May be repeated if there are multiple certificates to use for the server." << std::endl
              << "    --trusted-ca=PATH  Path to a PEM file holding trusted CA certificate(s)." << std::endl
              << "                       May be repeated." << std::endl
              << "                       Example path: \"/etc/ssl/certs/ca-certificates.crt\"" << std::endl
#endif
              << std::endl;
}