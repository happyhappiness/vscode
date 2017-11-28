bool
dirlevel( const char* dirname, const REList* list, bool level=false )
// purpose: from given starting point, look for squid 00..FF directories.
// paramtr: dirname (IN): starting point
//          list (IN): list of rexps to match URLs against
//          level (IN): false==toplevel, true==1st level
// example: "/var/spool/cache", false as input, traverse subdirs w/ action.
// example: "/var/spool/cache/08", true as input, traverse subdirs w/ action.
// returns: true, if every subdir && action was successful.
// warning: this function is once-recursive, no deeper.
{
    dirent_t* entry;
    if ( debugFlag & 0x01 )
        fprintf( stderr, "# [%d] %s\n", (level ? 1 : 0), dirname );

    DIR* dir = opendir( dirname );
    if ( dir == NULL ) {
        fprintf( stderr, "unable to open directory \"%s\": %s\n",
                 dirname, strerror(errno) );
        return false;
    }

    bool flag = true;
    while ( (entry=readdir(dir)) && flag ) {
        if ( strlen(entry->d_name) == 2 &&
                isxdigit(entry->d_name[0]) &&
                isxdigit(entry->d_name[1]) ) {
            char* name = concat( dirname, "/", entry->d_name, 0 );
            flag = level ? filelevel( name, list ) : dirlevel( name, list, true );
            delete[] name;
        }
    }

    closedir(dir);
    return flag;
}