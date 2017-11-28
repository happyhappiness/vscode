void
fd_note(int fd, const char *s)
{
    fde *F = &fd_table[fd];
    if (s)
        xstrncpy(F->desc, s, FD_DESC_SZ);
    else
        *(F->desc) = 0; // ""-string
}