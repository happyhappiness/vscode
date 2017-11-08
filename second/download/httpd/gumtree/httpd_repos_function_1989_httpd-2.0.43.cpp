static void stop_child_console_handler(void)
{
    SetConsoleCtrlHandler(child_control_handler, FALSE);
}