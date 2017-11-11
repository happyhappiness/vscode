void mpm_nt_eventlog_stderr_flush(void)
{
    HANDLE cleanup_thread = stderr_thread;

    if (cleanup_thread) {
        HANDLE hErr = GetStdHandle(STD_ERROR_HANDLE);
        fclose(stderr);
        CloseHandle(hErr);
        WaitForSingleObject(cleanup_thread, 30000);
        CloseHandle(cleanup_thread);
    }
}