int
Math::intAverage(const int cur, const int newI, int n, const int max)
{
    if (n > max)
        n = max;

    return (cur * (n - 1) + newI) / n;
}