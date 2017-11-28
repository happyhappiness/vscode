static void
usage(const char *progname)
{
    std::cerr << "Version: " << VERSION << std::endl
              << "Usage: " << progname << " [Basic Options] [HTTP Options]" << std::endl
              << std::endl;
    std::cerr
            << "    -s | --quiet    Silent.  Do not print response message to stdout." << std::endl
            << "    -v | --verbose  Verbose debugging. Repeat (-vv) to increase output level." << std::endl
            << "                    Levels:" << std::endl
            << "                      1 - Print outgoing request message to stderr." << std::endl
            << "                      2 - Print action trace to stderr." << std::endl
            << "    --help          Display this help text." << std::endl
            << std::endl;
    Transport::Config.usage();
    Ping::Config.usage();
    std::cerr
            << "HTTP Options:" << std::endl
            << "    -a           Do NOT include Accept: header." << std::endl
            << "    -A           User-Agent: header. Use \"\" to omit." << std::endl
            << "    -H 'string'  Extra headers to send. Use '\\n' for new lines." << std::endl
            << "    -i IMS       If-Modified-Since time (in Epoch seconds)." << std::endl
            << "    -j hosthdr   Host header content" << std::endl
            << "    -k           Keep the connection active. Default is to do only one request then close." << std::endl
            << "    -m method    Request method, default is GET." << std::endl
#if HAVE_GSSAPI
            << "    -n           Proxy Negotiate(Kerberos) authentication" << std::endl
            << "    -N           WWW Negotiate(Kerberos) authentication" << std::endl
#endif
            << "    -P file      Send content from the named file as request payload" << std::endl
            << "    -r           Force cache to reload URL" << std::endl
            << "    -t count     Trace count cache-hops" << std::endl
            << "    -u user      Proxy authentication username" << std::endl
            << "    -U user      WWW authentication username" << std::endl
            << "    -V version   HTTP Version. Use '-' for HTTP/0.9 omitted case" << std::endl
            << "    -w password  Proxy authentication password" << std::endl
            << "    -W password  WWW authentication password" << std::endl
            ;
    exit(1);
}