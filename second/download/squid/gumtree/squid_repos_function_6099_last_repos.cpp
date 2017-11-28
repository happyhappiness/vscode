void
File::writeAll(const SBuf &data)
{
#if _SQUID_WINDOWS_
    DWORD nBytesWritten = 0;
    if (!WriteFile(fd_, data.rawContent(), data.length(), &nBytesWritten, nullptr)) {
        const auto savedError = GetLastError();
        throw TexcHere(sysCallFailure("WriteFile", WindowsErrorMessage(savedError).c_str()));
    }
    const auto bytesWritten = static_cast<size_t>(nBytesWritten);
#else
    const auto result = ::write(fd_, data.rawContent(), data.length());
    if (result < 0) {
        const auto savedErrno = errno;
        throw TexcHere(sysCallError("write", savedErrno));
    }
    const auto bytesWritten = static_cast<size_t>(result);
#endif
    if (bytesWritten != data.length())
        throw TexcHere(sysCallFailure("write", "partial write"));
}