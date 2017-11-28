void
pipe_handler(int sig)
{
    std::cerr << "SIGPIPE received." << std::endl;
}