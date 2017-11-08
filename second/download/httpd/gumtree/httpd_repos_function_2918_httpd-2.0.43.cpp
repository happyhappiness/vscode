const char *apr_signal_description_get(int signum)
{
    switch (signum)
    {
    case SIGABRT:
        return "Abort";
    case SIGFPE:
        return "Arithmetic exception";
    case SIGILL:
        return "Illegal instruction";
    case SIGINT:
        return "Interrupt";
    case SIGSEGV:
        return "Segmentation fault";
    case SIGTERM:
        return "Terminated";
    case SIGPOLL:
        return "Pollable event occurred";
    default:
        return "unknown signal (not supported)";
    }
}