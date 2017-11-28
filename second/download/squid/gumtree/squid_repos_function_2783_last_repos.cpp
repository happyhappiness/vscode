const SBuf &
URL::SlashPath()
{
    static SBuf slash("/");
    return slash;
}