int
assert_copydir( const char* copydir )
// purpose: check, if copydir is a directory and that we can write into it.
// paramtr: copydir (IN): name of directory for copying bodies.
// returns: 0 if ok, -1 otherwise.
// further: errors are handled within. If the directory does not exist,
//          the assertion function will try to create it.
{
    struct stat st;
    int status = stat( copydir, &st );

    // check, if either "copydir" points to a valid directory,
    // or if copydir can be created.
    if ( status == 0 && ! S_ISDIR(st.st_mode) ) {
        // stat() returned true, but did not point to a directory
        fprintf( stderr, "copy dir \"%s\" is a file!\n", copydir );
        return -1;
    } else if ( S_ISDIR(st.st_mode) &&
                !( (st.st_uid == geteuid() && ( (st.st_mode & S_IWUSR) > 0 )) ||
                   (st.st_gid == getegid() && ( (st.st_mode & S_IWGRP) > 0 )) ||
                   ((st.st_mode & S_IWOTH) > 0) ) ) {
        fprintf( stderr, "copy dir \"%s\" is not accessible to me\n", copydir );
        return -1;
    }
    if ( status == -1 ) {
        // stat() returned with an error. 'File not found' is a legal error.
        if ( errno != ENOENT ) {
            // not a 'file not found' error, so this is hard error.
            fprintf( stderr, "accessing copy-out dir \"%s\": %s\n",
                     copydir, strerror(errno) );
            return -1;
        } else {
            // directory does not exist. Try to create it.
            if ( mkdir( copydir, 0750 ) == -1 ) {
                fprintf( stderr, "mkdir(%s): %s\n", copydir, strerror(errno) );
                return -1;
            }
        }
    }

    // postcondition: copydir exists and is a directory.
    return 0;
}