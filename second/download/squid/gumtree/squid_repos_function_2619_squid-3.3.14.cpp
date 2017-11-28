bool
InDaemonMode()
{
    return !opt_no_daemon && Config.workers > 0;
}