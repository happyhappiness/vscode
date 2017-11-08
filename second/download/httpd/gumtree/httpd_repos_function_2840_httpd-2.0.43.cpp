static apr_filetype_e filetype_from_mode(mode_t mode)
{
    apr_filetype_e type = APR_NOFILE;

    if (S_ISREG(mode))
        type = APR_REG;
    if (S_ISDIR(mode))
        type = APR_DIR;
    if (S_ISCHR(mode))
        type = APR_CHR;
    if (S_ISBLK(mode))
        type = APR_BLK;
    if (S_ISFIFO(mode))
        type = APR_PIPE;
    if (S_ISLNK(mode))
        type = APR_LNK;
#if !defined(BEOS) && defined(S_ISSOCK)
    if (S_ISSOCK(mode))
        type = APR_SOCK;
#endif
    return type;
}