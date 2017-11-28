int
main(int argc, char **argv)
{
#if USE_WIN32_SERVICE
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    if ((argc == 2) && strstr(argv[1], _WIN_SQUID_SERVICE_OPTION))
        return WIN32_StartService(argc, argv);
    else {
        WIN32_run_mode = _WIN_SQUID_RUN_MODE_INTERACTIVE;
        opt_no_daemon = 1;
    }
#endif

    return SquidMainSafe(argc, argv);
}