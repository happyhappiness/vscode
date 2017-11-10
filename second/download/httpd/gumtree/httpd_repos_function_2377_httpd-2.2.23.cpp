static void stop_console_handler(void)
{
    SetConsoleCtrlHandler(console_control_handler, FALSE);
}