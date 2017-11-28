static bool
mainChangeDir(const char *dir)
{
    if (chdir(dir) == 0)
        return true;

    int xerrno = errno;
    debugs(50, DBG_CRITICAL, "ERROR: cannot change current directory to " << dir <<
           ": " << xstrerr(xerrno));
    return false;
}