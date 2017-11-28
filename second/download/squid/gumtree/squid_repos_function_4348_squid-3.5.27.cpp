const SBuf &
Ftp::cmdStat()
{
    static const SBuf cmd("STAT");
    return cmd;
}