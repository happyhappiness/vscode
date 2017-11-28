void WIN32_ExceptionHandlerCleanup()
{
    if (Win32_Old_ExceptionHandler != NULL)
        SetUnhandledExceptionFilter(Win32_Old_ExceptionHandler);
}