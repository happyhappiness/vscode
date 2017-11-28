void
fwdUninit(void)
{
    if (NULL == logfile)
        return;

    logfileClose(logfile);

    logfile = NULL;
}