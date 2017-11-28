double
statHistDeltaMedian(const StatHist * A, const StatHist * B)
{
    return statHistDeltaPctile(A, B, 0.5);
}