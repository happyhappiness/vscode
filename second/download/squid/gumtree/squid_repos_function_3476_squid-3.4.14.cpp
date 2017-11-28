void WIN32_ExceptionHandlerInit()
{
#if !defined(_DEBUG)

    if (Win32_Old_ExceptionHandler == NULL)
        Win32_Old_ExceptionHandler = SetUnhandledExceptionFilter(WIN32_ExceptionHandler);

#endif
}