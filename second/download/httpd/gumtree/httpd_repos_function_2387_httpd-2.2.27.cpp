void mpm_start_child_console_handler(void)
{
    if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT) {
        FreeConsole();
    }
    else
    {
        SetConsoleCtrlHandler(child_control_handler, TRUE);
        atexit(stop_child_console_handler);
    }
}