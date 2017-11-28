void
Ping::TheConfig::usage()
{
    std::cerr << "Ping Mode" << std::endl
              << "  --ping [options]  Enable ping mode." << std::endl
              << std::endl
              << "  options:" << std::endl
              << "    -g count        Ping iteration count (default, loop until interrupted)." << std::endl
              << "    -I interval     Ping interval in seconds (default 1 second)." << std::endl
              << std::endl;
}