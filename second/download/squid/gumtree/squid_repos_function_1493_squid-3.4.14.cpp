static bool
mainChangeDir(const char *dir)
{
    if (chdir(dir) == 0)
        return true;

    debugs(50, DBG_CRITICAL, "cannot change current directory to " << dir <<
           ": " << xstrerror());
    return false;
}