char *
Get_WIN32_ErrorMessage(HRESULT hr)
{
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                  FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL,
                  hr,
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                  (LPTSTR) & WIN32_ErrorMessage,
                  0,
                  NULL);
    return WIN32_ErrorMessage;
}