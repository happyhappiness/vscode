bool
Transport::TheConfig::parseCommandOpts(int argc, char *argv[], int c, int &optIndex)
{
    bool tls = false;
    const char *shortOpStr = "h:l:p:T:?";

    // options for controlling squidclient transport connection
    static struct option longOptions[] = {
        {"anonymous-tls",no_argument, 0, '\1'},
        {"https",        no_argument, 0, '\3'},
        {"trusted-ca",   required_argument, 0, 'A'},
        {"cert",         required_argument, 0, 'C'},
        {"host",         required_argument, 0, 'h'},
        {"local",        required_argument, 0, 'l'},
        {"port",         required_argument, 0, 'p'},
        {"params",       required_argument, 0, 'P'},
        {0, 0, 0, 0}
    };

    int saved_opterr = opterr;
    opterr = 0; // suppress errors from getopt
    do {
        switch (c) {
        case '\1':
            tls = true;
            tlsAnonymous = true;
            params = "PERFORMANCE:+ANON-ECDH:+ANON-DH";
            break;

        case '\3':
            tls = true;
            break;

        case 'A':
            tls = true;
            caFiles.push_back(std::string(optarg));
            break;

        case 'C':
            tls = true;
            certFiles.push_back(std::string(optarg));
            break;

        case 'h':
            hostname = optarg;
            break;

        case 'l':
            localHost = optarg;
            break;

        case 'p':           /* port number */
            sscanf(optarg, "%hd", &port);
            if (port < 1)
                port = CACHE_HTTP_PORT;     /* default */
            break;

        case 'P':
            tls = true;
            params = optarg;
            break;

        case 'T':
            ioTimeout = atoi(optarg);
            break;

        default:
            if (tls)
                Transport::InitTls();

            // rewind and let the caller handle unknown options
            --optind;
            opterr = saved_opterr;
            return true;
        }
    } while ((c = getopt_long(argc, argv, shortOpStr, longOptions, &optIndex)) != -1);

    if (tls)
        Transport::InitTls();

    opterr = saved_opterr;
    return false;
}