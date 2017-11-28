static void
usage(const char *progname)
{
    fprintf(stderr,
            "Version: %s\n"
            "Usage: %s [-arsv] [-A 'string'] [-g count] [-h remote host] [-H 'string'] [-i IMS] [-I ping-interval] [-j 'Host-header']"
            "[-k] [-l local-host] [-m method] "
#if HAVE_GSSAPI
            "[-n] [-N] "
#endif
            "[-p port] [-P file] [-t count] [-T timeout] [-u proxy-user] [-U www-user] "
            "[-V version] [-w proxy-password] [-W www-password] url\n"
            "\n"
            "Options:\n"
            "    -a           Do NOT include Accept: header.\n"
            "    -A           User-Agent: header. Use \"\" to omit.\n"
            "    -g count     Ping mode, perform \"count\" iterations (0 to loop until interrupted).\n"
            "    -h host      Retrieve URL from cache on hostname.  Default is localhost.\n"
            "    -H 'string'  Extra headers to send. Use '\\n' for new lines.\n"
            "    -i IMS       If-Modified-Since time (in Epoch seconds).\n"
            "    -I interval  Ping interval in seconds (default 1 second).\n"
            "    -j hosthdr   Host header content\n"
            "    -k           Keep the connection active. Default is to do only one request then close.\n"
            "    -l host      Specify a local IP address to bind to.  Default is none.\n"
            "    -m method    Request method, default is GET.\n"
#if HAVE_GSSAPI
            "    -n           Proxy Negotiate(Kerberos) authentication\n"
            "    -N           WWW Negotiate(Kerberos) authentication\n"
#endif
            "    -p port      Port number of cache.  Default is %d.\n"
            "    -P file      PUT request. Using the named file\n"
            "    -r           Force cache to reload URL.\n"
            "    -s           Silent.  Do not print data to stdout.\n"
            "    -t count     Trace count cache-hops\n"
            "    -T timeout   Timeout value (seconds) for read/write operations.\n"
            "    -u user      Proxy authentication username\n"
            "    -U user      WWW authentication username\n"
            "    -v           Verbose. Print outgoing message to stderr.\n"
            "    -V version   HTTP Version. Use '-' for HTTP/0.9 omitted case\n"
            "    -w password  Proxy authentication password\n"
            "    -W password  WWW authentication password\n",
            VERSION, progname, CACHE_HTTP_PORT);
    exit(1);
}