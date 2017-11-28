int Adaptation::History::Entry::rptm()
{
    if (theRptm < 0)
        theRptm = tvSubMsec(start, current_time);
    return theRptm;
}