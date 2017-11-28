void
fwdLogRotate(void)
{
    if (logfile)
        logfileRotate(logfile);
}