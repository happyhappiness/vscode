void
pipe_handler(int)
{
    std::cerr << "SIGPIPE received." << std::endl;
}