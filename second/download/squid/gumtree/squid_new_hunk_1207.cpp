    }
#elif _SQUID_LINUX_
    Ip::Interceptor.StopTransparency("Missing needed capability support.");
#endif /* HAVE_SYS_CAPABILITY_H */
}

pid_t
WaitForOnePid(pid_t pid, PidStatus &status, int flags)
{
#if _SQUID_NEXT_
    if (pid < 0)
        return wait3(&status, flags, NULL);
    return wait4(pid, &status, flags, NULL);
#elif _SQUID_WINDOWS_
    return 0; // function not used on Windows
#else
    return waitpid(pid, &status, flags);
#endif
}

#if _SQUID_WINDOWS_
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
#endif // _SQUID_WINDOWS_

