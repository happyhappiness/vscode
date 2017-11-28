void
CloseCOM(void)
{
    if (WIN32_COM_initialized == 1)
        CoUninitialize();
}