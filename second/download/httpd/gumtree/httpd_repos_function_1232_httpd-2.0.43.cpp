static int ftp_check_globbingchars(const char *path)
{
    for ( ; *path; ++path) {
        if (*path == '\\')
	    ++path;
        if (path != '\0' && strchr(FTP_GLOBBING_CHARS, *path) != NULL)
            return TRUE;
    }
    return FALSE;
}