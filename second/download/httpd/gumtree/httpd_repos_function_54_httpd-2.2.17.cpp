static void usage(void)
{
    const char *have_sdbm;
    const char *have_gdbm;
    const char *have_ndbm;
    const char *have_db;

#if APU_HAVE_SDBM
    have_sdbm = AVAIL;
#else
    have_sdbm = UNAVAIL;
#endif
#if APU_HAVE_GDBM
    have_gdbm = AVAIL;
#else
    have_gdbm = UNAVAIL;
#endif
#if APU_HAVE_NDBM
    have_ndbm = AVAIL;
#else
    have_ndbm = UNAVAIL;
#endif
#if APU_HAVE_DB
    have_db = AVAIL;
#else
    have_db = UNAVAIL;
#endif

    apr_file_printf(errfile,
    "%s -- Program to Create DBM Files for use by RewriteMap" NL
    "Usage: %s [-v] [-f format] -i SOURCE_TXT -o OUTPUT_DBM" NL
    NL
    "Options: " NL
    " -v    More verbose output"NL
    NL
    " -i    Source Text File. If '-', use stdin."NL
    NL
    " -o    Output DBM."NL
    NL
    " -f    DBM Format.  If not specified, will use the APR Default." NL
    "           GDBM for GDBM files (%s)" NL
    "           SDBM for SDBM files (%s)" NL
    "           DB   for berkeley DB files (%s)" NL
    "           NDBM for NDBM files (%s)" NL
    "           default for the default DBM type" NL
    NL,
    shortname,
    shortname,
    have_gdbm,
    have_sdbm,
    have_db,
    have_ndbm);
}