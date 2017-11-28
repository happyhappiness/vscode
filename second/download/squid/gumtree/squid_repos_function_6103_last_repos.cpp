SBuf
File::sysCallFailure(const char *callName, const char *error) const
{
    return ToSBuf("failed to ", callName, ' ', name_, ": ", error);
}