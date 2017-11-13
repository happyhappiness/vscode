static void print_statistics (apr_file_t *output)
{
    apr_file_printf(output, "logresolve Statistics:" NL);
    apr_file_printf(output, "Entries: %d" NL, entries);
    apr_file_printf(output, "    With name   : %d" NL, withname);
    apr_file_printf(output, "    Resolves    : %d" NL, resolves);

    if (noreverse) {
        apr_file_printf(output, "    - No reverse : %d" NL,
                        noreverse);
    }

    if (doublefailed) {
        apr_file_printf(output, "    - Double lookup failed : %d" NL,
                        doublefailed);
    }

    apr_file_printf(output, "Cache hits      : %d" NL, cachehits);
    apr_file_printf(output, "Cache size      : %d" NL, cachesize);
}