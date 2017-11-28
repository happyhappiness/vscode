static void
logfile_mod_daemon_rotate(Logfile * lf)
{
    char tb[3];
    debugs(50, DBG_IMPORTANT, "logfileRotate: " << lf->path);
    tb[0] = 'R';
    tb[1] = '\n';
    tb[2] = '\0';
    logfile_mod_daemon_append(lf, tb, 2);
}