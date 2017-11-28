void
UFSSwapDir::create()
{
    debugs(47, 3, "Creating swap space in " << path);
    createDirectory(path, 0);
    createSwapSubDirs();
}