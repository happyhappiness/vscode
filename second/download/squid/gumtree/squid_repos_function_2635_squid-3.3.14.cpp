void
setUmask(mode_t mask)
{
    // No way to get the current umask value without setting it.
    static const mode_t orig_umask = umask(mask); // once, to get
    umask(mask | orig_umask); // always, to set
}