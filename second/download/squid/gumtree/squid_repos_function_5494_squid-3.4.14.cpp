void
logfileClose(Logfile * lf)
{
    debugs(50, DBG_IMPORTANT, "Logfile: closing log " << lf->path);
    lf->f_flush(lf);
    lf->f_close(lf);
    cbdataFree(lf);
}