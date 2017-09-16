    if (r->finfo.st_mode == 0         /* doesn't exist */

        || S_ISDIR(r->finfo.st_mode)

        || S_ISREG(r->finfo.st_mode)

        || S_ISLNK(r->finfo.st_mode)) {

        return OK;

    }

    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,

                "object is not a file, directory or symlink: %s",

                r->filename);

    return HTTP_FORBIDDEN;

}





static int check_symlinks(char *d, int opts)

{

#if defined(__EMX__) || defined(WIN32)

    /* OS/2 doesn't have symlinks */

    return OK;

#else

    struct stat lfi, fi;

    char *lastp;

    int res;

