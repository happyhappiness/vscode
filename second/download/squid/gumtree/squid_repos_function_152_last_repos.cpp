bool
Ping::TheConfig::parseCommandOpts(int argc, char *argv[], int c, int &optIndex)
{
    // to get here --ping was seen
    enable = true;
    count = 0;           // default is infinite loop
    interval = 1 * 1000; // default is 1s intervals

    const char *shortOpStr = "g:I:?";

    // options for controlling squidclient ping mode
    static struct option pingOptions[] = {
        {"count",    no_argument, 0, 'g'},
        {"interval", no_argument, 0, 'I'},
        {0, 0, 0, 0}
    };

    int saved_opterr = opterr;
    opterr = 0; // suppress errors from getopt
    while ((c = getopt_long(argc, argv, shortOpStr, pingOptions, &optIndex)) != -1) {
        switch (c) {
        case 'g':
            if (optarg)
                count = atoi(optarg);
            else {
                std::cerr << "ERROR: -g ping count missing parameter." << std::endl;
                usage();
            }
            break;

        case 'I':
            if (!optarg) {
                std::cerr << "ERROR: -I ping interval missing parameter." << std::endl;
                usage();
            } else if ((interval = atoi(optarg) * 1000) <= 0) {
                std::cerr << "ERROR: -I ping interval out of range (0-" << (INT_MAX/1000) << ")." << std::endl;
                usage();
            }
            break;

        default:
            // rewind and let the caller handle unknown options
            --optind;
            opterr = saved_opterr;
            return true;
        }
    }

    opterr = saved_opterr;
    return false;
}