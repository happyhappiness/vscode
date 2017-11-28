static void
idnsRcodeCount(int rcode, int attempt)
{
    if (rcode > 0)
        rcode = 0;
    else if (rcode < 0)
        rcode = -rcode;

    if (rcode < MAX_RCODE)
        if (attempt < MAX_ATTEMPT)
            RcodeMatrix[rcode][attempt]++;
}