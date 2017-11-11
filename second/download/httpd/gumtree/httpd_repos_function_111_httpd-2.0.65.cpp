DWORD WINAPI feedback(LPVOID arg)
{
    feedback_args_t *feed = (feedback_args_t*)arg;
    char *str[1024];
    DWORD len;

    while (ReadFile(feed->in, str, sizeof(str), &len, NULL))
        if (!len || !WriteFile(feed->out, str, len, &len, NULL))
            break;

    printerr("[EOF] from Console (%d)\n", GetLastError());

    return 0;
}