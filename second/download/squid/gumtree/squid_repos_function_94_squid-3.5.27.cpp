bool
filelevel( const char* directory, const REList* list )
// purpose: from given starting point, look for squid xxxxxxxx files.
// example: "/var/spool/cache/08/7F" as input, do action over files
// paramtr: directory (IN): starting point
//          list (IN): list of rexps to match URLs against
// returns: true, if every subdir && action was successful.
{
    dirent_t * entry;
    if ( debugFlag & 0x01 )
        fprintf( stderr, "# [2] %s\n", directory );

    DIR* dir = opendir( directory );
    if ( dir == NULL ) {
        fprintf( stderr, "unable to open directory \"%s\": %s\n",
                 directory, strerror(errno) );
        return false;
    }

    // display a rotating character as "i am alive" signal (slows purge).
    if ( ::iamalive ) {
        static char alivelist[4][3] = { "\\\b", "|\b", "/\b", "-\b" };
        static unsigned short alivecount = 0;
        const int write_success = write(STDOUT_FILENO, alivelist[alivecount++ & 3], 2);
        assert(write_success == 2);
    }

    bool flag = true;
    while ( (entry=readdir(dir)) && flag ) {
        if ( isxstring(entry->d_name,8) ) {
            char* name = concat( directory, "/", entry->d_name, 0 );
            flag = match( name, list );
            delete[] name;
        }
    }

    closedir(dir);
    return flag;
}