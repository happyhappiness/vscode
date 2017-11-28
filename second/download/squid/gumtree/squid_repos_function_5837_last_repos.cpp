static void
process_options(int argc, char *argv[])
{
    int opt;

    opterr = 0;
    while (-1 != (opt = getopt(argc, argv, "hd"))) {
        switch (opt) {
        case 'd':
            debug_enabled = 1;
            break;
        case 'h':
            usage();
            exit(0);
        default:
            std::cerr << program_name << ": FATAL: unknown option: -" <<
                      static_cast<char>(optopt) << ". Exiting" << std::endl;
            usage();
            exit(1);
        }
    }
}