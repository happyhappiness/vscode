void
logfileLineEnd(Logfile * lf)
{
    lf->f_lineend(lf);
    ++ lf->sequence_number;
}