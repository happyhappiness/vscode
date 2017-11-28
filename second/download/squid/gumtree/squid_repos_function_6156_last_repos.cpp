static void
logfile_mod_daemon_linestart(Logfile * lf)
{
    l_daemon_t *ll = static_cast<l_daemon_t *>(lf->data);
    char tb[2];
    assert(ll->eol == 1);
    ll->eol = 0;
    tb[0] = 'L';
    tb[1] = '\0';
    logfile_mod_daemon_append(lf, tb, 1);
}