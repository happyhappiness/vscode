SBuf
File::readSmall(const SBuf::size_type minBytes, const SBuf::size_type maxBytes)
{
    SBuf buf;
    const auto readLimit = maxBytes + 1; // to detect excessively large files that we do not handle
#if _SQUID_WINDOWS_
    DWORD result = 0;
    if (!ReadFile(fd_, buf.rawSpace(readLimit), readLimit, &result, nullptr)) {
        const auto savedError = GetLastError();
        throw TexcHere(sysCallFailure("ReadFile", WindowsErrorMessage(savedError).c_str()));
    }
#else
    const auto result = ::read(fd_, buf.rawSpace(readLimit), readLimit);
    if (result < 0) {
        const auto savedErrno = errno;
        throw TexcHere(sysCallError("read", savedErrno));
    }
#endif
    const auto bytesRead = static_cast<size_t>(result);
    assert(bytesRead <= readLimit);
    Must(!buf.length());
    buf.forceSize(bytesRead);

    if (buf.length() < minBytes) {
        const auto failure = buf.length() ? "premature eof" : "empty file";
        throw TexcHere(sysCallFailure("read", failure));
    }

    if (buf.length() > maxBytes) {
        const auto failure = "unreasonably large file";
        throw TexcHere(sysCallFailure("read", failure));
    }

    Must(minBytes <= buf.length() && buf.length() <= maxBytes);
    return buf;
}