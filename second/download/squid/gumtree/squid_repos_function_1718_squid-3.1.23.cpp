void
statHistLogInit(StatHist * H, int capacity, double min, double max)
{
    statHistInit(H, capacity, Log, Exp, min, max);
}