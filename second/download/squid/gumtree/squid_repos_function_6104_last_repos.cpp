SBuf
File::sysCallError(const char *callName, const int savedErrno) const
{
    return sysCallFailure(callName, xstrerr(savedErrno));
}