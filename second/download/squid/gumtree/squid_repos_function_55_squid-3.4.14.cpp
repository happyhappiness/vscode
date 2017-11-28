int
readConfigFile( CacheDirVector& cachedir, const char* fn, FILE* debug )
// purpose: read squid.conf file and extract cache_dir entries
// paramtr: cachedir (OUT): vector with an entry for each cache_dir found
//          fn (IN): file name of squid.conf to use
// returns: number of entries, or negative to warn of errors
{
    static const char* expression =
        "^[ \t]*cache_dir([ \t]+([[:alpha:]]+))?[ \t]+([[:graph:]]+)[ \t]+([0-9]+)[ \t]+([0-9]+)[ \t]+([0-9]+)";

    // try to open file
    if ( debug ) fprintf( debug, "# trying to open %s\n", fn ? fn : "(null)" );
    std::ifstream cfgin(fn);
    if (!cfgin) {
        fprintf( stderr, "fopen %s: %s\n", fn, strerror(errno) );
        return -1;
    }

    // prepare regular expression for matching
    if ( debug ) fprintf( debug, "# trying to compile \"%s\"\n", expression );
    regex_t rexp;
    int result = regcomp( &rexp, expression, REG_EXTENDED );
    if ( result != 0 ) {
        char buffer[256];
        regerror( result, &rexp, buffer, sizeof(buffer) );
        fprintf( stderr, "regular expression \"%s\": %s\n", expression, buffer );
        return -1;
    }

    // read line by line
    if ( debug ) fputs( "# trying to read lines\n", debug );

    regmatch_t subs[8];
    char *s, line[1024];
    CacheDir cd;
    while ( cfgin.getline( line, sizeof(line)) ) {
        // FIXME: overly long lines

        // terminate line at start of comment
        if ( (s = (char*) memchr( line, '#', sizeof(line) )) ) *s = '\0';

        // quick skip
        if ( *line == '\0' || *line == '\n' ) continue;

        // test line
        if ( (result=regexec( &rexp, line, 7, subs, 0 )) != 0 ) {
            // error or no match
            if ( result != REG_NOMATCH ) {
                char buffer[256];
                regerror( result, &rexp, buffer, sizeof(buffer) );
                fprintf( stderr, "while matching \"%s\" against %s%s\n",
                         expression, line, buffer );
                regfree(&rexp);
                cfgin.close();
                return -1;
            }
        } else {
            // match, please record
            memset( &cd, 0, sizeof(cd) );
            if ( debug ) fprintf( debug, "# match from %d-%d on line %s",
                                      (int)subs[0].rm_so, (int)subs[0].rm_eo,
                                      line );

            // terminate line after matched expression
            line[ subs[0].rm_eo ] = '\0';

            // extract information. If 6th parenthesis is filled, this is
            // a new squid with disk types, otherwise it is an older version
            int offset = 2;
            if ( subs[6].rm_so == -1 ) {
                // old version, disk type at position 2 is always UFS
                cd.type = CacheDir::CDT_UFS;
            } else {
                // new version, disk type at position 2
                line[ subs[offset].rm_eo ] = '\0';
                if ( debug ) fprintf( debug, "# match from %d-%d on \"%s\"\n",
                                          (int)subs[offset].rm_so,
                                          (int)subs[offset].rm_eo,
                                          line+subs[offset].rm_so );
                if ( strcmp( line + subs[offset].rm_so, "ufs" ) == 0 )
                    cd.type = CacheDir::CDT_UFS;
                else if ( strcmp( line + subs[offset].rm_so, "asyncufs" ) == 0 )
                    cd.type = CacheDir::CDT_AUFS;
                else if ( strcmp( line + subs[offset].rm_so, "diskd" ) == 0 )
                    cd.type = CacheDir::CDT_DISKD;
                else
                    cd.type = CacheDir::CDT_OTHER;
                ++offset;
            }

            // extract base directory
            line[ subs[offset].rm_eo ] = '\0';
            if ( debug ) fprintf( debug, "# match from %d-%d on \"%s\"\n",
                                      (int)subs[offset].rm_so,
                                      (int)subs[offset].rm_eo,
                                      line+subs[offset].rm_so );
            cd.base = strdup( line+subs[offset].rm_so );
            ++offset;

            // extract size information
            line[ subs[offset].rm_eo ] = '\0';
            if ( debug ) fprintf( debug, "# match from %d-%d on \"%s\"\n",
                                      (int)subs[offset].rm_so,
                                      (int)subs[offset].rm_eo,
                                      line+subs[offset].rm_so );
            cd.size = strtoul( line+subs[offset].rm_so, 0, 10 );
            ++offset;

            // extract 1st level directories
            line[ subs[offset].rm_eo ] = '\0';
            if ( debug ) fprintf( debug, "# match from %d-%d on \"%s\"\n",
                                      (int)subs[offset].rm_so,
                                      (int)subs[offset].rm_eo,
                                      line+subs[offset].rm_so );
            cd.level[0] = strtoul( line+subs[offset].rm_so, 0, 10 );
            ++offset;

            // extract 2nd level directories
            line[ subs[offset].rm_eo ] = '\0';
            if ( debug ) fprintf( debug, "# match from %d-%d on \"%s\"\n",
                                      (int)subs[offset].rm_so,
                                      (int)subs[offset].rm_eo,
                                      line+subs[offset].rm_so );
            cd.level[1] = strtoul( line+subs[offset].rm_so, 0, 10 );
            ++offset;

            cachedir.push_back( cd );
        }
    }

    cfgin.close();
    regfree(&rexp);
    return cachedir.size();
}