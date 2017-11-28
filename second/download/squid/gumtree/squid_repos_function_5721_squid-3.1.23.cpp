int
xpercentInt(double part, double whole)
{
#if HAVE_RINT
    return (int) rint(xpercent(part, whole));
#else
    /* SCO 3.2v4.2 doesn't have rint() -- mauri@mbp.ee */
    return (int) floor(xpercent(part, whole) + 0.5);
#endif
}