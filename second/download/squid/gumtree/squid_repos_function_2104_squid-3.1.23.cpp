void
death(int sig)
{
    std::cout << "Fatal: Signal " <<  sig;
    exit(1);
}