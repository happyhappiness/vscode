SBuf
WindowsErrorMessage(DWORD errorId)
{
    char *rawMessage = nullptr;
    const auto length = FormatMessage(
                            FORMAT_MESSAGE_ALLOCATE_BUFFER |
                            FORMAT_MESSAGE_FROM_SYSTEM |
                            FORMAT_MESSAGE_IGNORE_INSERTS,
                            nullptr,
                            errorId,
                            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                            static_cast<LPTSTR>(&rawMessage),
                            0,
                            nullptr);
    if (!length) {
        Must(!rawMessage); // nothing to LocalFree()
        return ToSBuf("windows error ", errorId);
    }
    const auto result = SBuf(rawMessage, length);
    LocalFree(rawMessage);
    return result;
}