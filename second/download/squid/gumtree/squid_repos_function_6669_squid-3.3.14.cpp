struct dirent *
readdir(DIR * dirp) {
    errno = 0;

    /* Check for valid DIR struct. */
    if (!dirp) {
        errno = EFAULT;
        return (struct dirent *) 0;
    }
    if (dirp->dd_stat < 0) {
        /* We have already returned all files in the directory
         * (or the structure has an invalid dd_stat). */
        return (struct dirent *) 0;
    } else if (dirp->dd_stat == 0) {
        /* We haven't started the search yet. */
        /* Start the search */
        dirp->dd_handle = _findfirst(dirp->dd_name, &(dirp->dd_dta));

        if (dirp->dd_handle == -1) {
            /* Whoops! Seems there are no files in that
             * directory. */
            dirp->dd_stat = -1;
        } else {
            dirp->dd_stat = 1;
        }
    } else {
        /* Get the next search entry. */
        if (_findnext(dirp->dd_handle, &(dirp->dd_dta))) {
            /* We are off the end or otherwise error.
             * _findnext sets errno to ENOENT if no more file
             * Undo this. */
            DWORD winerr = GetLastError();
            if (winerr == ERROR_NO_MORE_FILES)
                errno = 0;
            _findclose(dirp->dd_handle);
            dirp->dd_handle = -1;
            dirp->dd_stat = -1;
        } else {
            /* Update the status to indicate the correct
             * number. */
            dirp->dd_stat++;
        }
    }

    if (dirp->dd_stat > 0) {
        /* Successfully got an entry. Everything about the file is
         * already appropriately filled in except the length of the
         * file name. */
        dirp->dd_dir.d_namlen = strlen(dirp->dd_dta.name);
        strcpy(dirp->dd_dir.d_name, dirp->dd_dta.name);
        return &dirp->dd_dir;
    }
    return (struct dirent *) 0;
}