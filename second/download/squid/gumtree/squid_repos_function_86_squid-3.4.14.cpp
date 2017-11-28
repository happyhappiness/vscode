static
    void
    exiter( void ) {
        if ( ::term_flag ) psignal( ::term_flag, "received signal" );
        delete[] ::linebuffer;
        if ( ::reminder ) {
            fputs(
                "WARNING! Caches files were removed. Please shut down your cache, remove\n"
                "your swap.state files and restart your cache again, i.e. effictively do\n"
                "a slow rebuild your cache! Otherwise your squid *will* choke!\n", stderr );
        }
    }