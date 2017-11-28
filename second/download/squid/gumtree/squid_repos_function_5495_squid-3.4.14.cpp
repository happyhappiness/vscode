void
logfileRotate(Logfile * lf)
{
    debugs(50, DBG_IMPORTANT, "logfileRotate: " << lf->path);
    lf->f_rotate(lf);
}