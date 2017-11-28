static
int
log_extended( const char* fn, int code, long size, const SquidMetaList* meta )
{
    static const char hexdigit[] = "0123456789ABCDEF";
    char md5[34];
    const SquidTLV* findings = 0;

    if ( meta && (findings = meta->search( STORE_META_KEY_MD5 )) ) {
        unsigned char* s = (unsigned char*) findings->data;
        for ( int j=0; j<16; ++j, ++s ) {
            md5[j*2+0] = hexdigit[ *s >> 4 ];
            md5[j*2+1] = hexdigit[ *s & 15 ];
        }
        md5[32] = '\0'; // terminate string
    } else {
        snprintf( md5, sizeof(md5), "%-32s", "(no_md5_data_available)" );
    }

    char timeb[256];
    if ( meta && (findings = meta->search( STORE_META_STD )) ) {
        StoreMetaStd temp;
        // make data aligned, avoid SIGBUS on RISC machines (ARGH!)
        memcpy( &temp, findings->data, sizeof(StoreMetaStd) );
        snprintf( timeb, sizeof(timeb), "%08lx %08lx %08lx %08lx %04x %5hu ",
                  (unsigned long)temp.timestamp, (unsigned long)temp.lastref,
                  (unsigned long)temp.expires, (unsigned long)temp.lastmod, temp.flags, temp.refcount );
    } else if ( meta && (findings = meta->search( STORE_META_STD_LFS )) ) {
        StoreMetaStdLFS temp;
        // make data aligned, avoid SIGBUS on RISC machines (ARGH!)
        memcpy( &temp, findings->data, sizeof(StoreMetaStdLFS) );
        snprintf( timeb, sizeof(timeb), "%08lx %08lx %08lx %08lx %04x %5hu ",
                  (unsigned long)temp.timestamp, (unsigned long)temp.lastref,
                  (unsigned long)temp.expires, (unsigned long)temp.lastmod, temp.flags, temp.refcount );
    } else {
        unsigned long ul = ULONG_MAX;  // Match type of StoreMetaTLV fields
        unsigned short hu = 0;  // Match type of StoreMetaTLV refcount fields
        snprintf( timeb, sizeof(timeb), "%08lx %08lx %08lx %08lx %04x %5d ", ul, ul, ul, ul, 0, hu);
    }

    // make sure that there is just one printf()
    if ( meta && (findings = meta->search( STORE_META_URL )) ) {
        return printf( "%s %3d %8ld %s %s %s\n",
                       fn, code, size, md5, timeb, findings->data );
    } else {
        return printf( "%s %3d %8ld %s %s strange_file\n",
                       fn, code, size, md5, timeb );
    }
}