static SBuf
PidFilename()
{
    const auto name = PidFilenameCalc();
    TheFile = PidFileDescription(name);
    return name;
}