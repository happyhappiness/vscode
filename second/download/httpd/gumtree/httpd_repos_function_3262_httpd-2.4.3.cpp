void mpm_start_console_handler(void)
{
    SetConsoleCtrlHandler(console_control_handler, TRUE);
    atexit(stop_console_handler);
}