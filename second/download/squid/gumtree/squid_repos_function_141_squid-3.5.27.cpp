static void
catchSignal(int sig)
{
    Ping::DisplayStats();
    Ping::Config.enable = false;
    std::cerr << "SIGNAL " << sig << " Interrupted." << std::endl;
}