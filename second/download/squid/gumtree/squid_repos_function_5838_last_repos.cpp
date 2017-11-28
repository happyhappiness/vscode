int
main(int argc, char *argv[])
{
    program_name = argv[0];
    process_options(argc, argv);

    ndebug(program_name << ' ' << VERSION << ' ' << SQUID_BUILD_INFO <<
           " starting up...");
    std::string buf;
    while (getline(std::cin,buf)) { // will return false at EOF
        ndebug("Got " << buf.length() << " bytes '" << buf << "' from Squid");

        /* send 'OK' result back to Squid */
        SEND_OK("");
    }
    ndebug(program_name << ' ' << VERSION << ' ' << SQUID_BUILD_INFO <<
           " shutting down...");
    return 0;
}