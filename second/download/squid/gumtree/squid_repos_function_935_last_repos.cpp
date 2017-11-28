static SBuf
PidFileDescription(const SBuf &filename)
{
    return ToSBuf("PID file (", filename, ')');
}