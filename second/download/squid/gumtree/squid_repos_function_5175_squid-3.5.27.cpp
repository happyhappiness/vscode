const char *
Rock::SwapDir::freeSlotsPath() const
{
    static String spacesPath;
    spacesPath = path;
    spacesPath.append("_spaces");
    return spacesPath.termedBuf();
}