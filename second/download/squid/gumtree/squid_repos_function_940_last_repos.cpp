pid_t
Instance::Other()
{
    const auto filename = PidFilename();
    if (filename.isEmpty())
        throw TexcHere("no pid_filename configured");

    File pidFile(filename, File::Be::ReadOnly().locked());
    return GetOtherPid(pidFile);
}