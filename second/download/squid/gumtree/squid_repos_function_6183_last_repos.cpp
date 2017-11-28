void
logfileRotate(Logfile * lf, int16_t rotateCount)
{
    debugs(50, DBG_IMPORTANT, "logfileRotate: " << lf->path);
    lf->f_rotate(lf, rotateCount);
}