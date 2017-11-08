static apr_filetype_e filetype_from_mode(mode_t mode)
{
    apr_filetype_e type;

    switch (mode & S_IFMT) {
    case S_IFREG:
        type = APR_REG;  break;
    case S_IFDIR:
        type = APR_DIR;  break;
    case S_IFLNK:
        type = APR_LNK;  break;
    case S_IFCHR:
        type = APR_CHR;  break;
    case S_IFBLK:
        type = APR_BLK;  break;
#if defined(S_IFFIFO)
    case S_IFFIFO:
        type = APR_PIPE; break;
#endif
#if !defined(BEOS) && defined(S_IFSOCK)
    case S_IFSOCK:
        type = APR_SOCK; break;
#endif

    default:
	/* Work around missing S_IFxxx values above
         * for Linux et al.
         */
#if !defined(S_IFFIFO) && defined(S_ISFIFO)
    	if (S_ISFIFO(mode)) {
            type = APR_PIPE;
	} else
#endif
#if !defined(BEOS) && !defined(S_IFSOCK) && defined(S_ISSOCK)
    	if (S_ISSOCK(mode)) {
            type = APR_SOCK;
	} else
#endif
        type = APR_UNKFILE;
    }
    return type;
}