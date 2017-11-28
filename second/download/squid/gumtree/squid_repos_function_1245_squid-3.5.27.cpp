int
DelayBucket::bytesWanted(int minimum, int maximum) const
{
    int result = max(minimum, min(maximum, level()));
    return result;
}