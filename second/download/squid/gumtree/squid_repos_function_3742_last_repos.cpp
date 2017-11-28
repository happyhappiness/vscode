const SBuf &
Ftp::cmdMlst()
{
    static const SBuf cmd("MLST");
    return cmd;
}