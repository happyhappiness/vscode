static apr_filetype_e filetype_from_mode(mode_t mode)
{
    apr_filetype_e type = APR_NOFILE;

    if (S_ISREG(mode))
        type = APR_REG;
    else if (S_ISDIR(mode))
        type = APR_DIR;
    else if (S_ISCHR(mode))
        type = APR_CHR;
    else if (S_ISBLK(mode))
        type = APR_BLK;
    else if (S_ISFIFO(mode))
        type = APR_PIPE;
    else if (S_ISLNK(mode))
        type = APR_LNK;
    else if (S_ISSOCK(mode))
        type = APR_SOCK;
    else
        type = APR_UNKFILE;
    return type;
}