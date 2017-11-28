double
Math::doubleAverage(const double cur, const double newD, int N, const int max)
{
    if (N > max)
        N = max;

    return (cur * (N - 1.0) + newD) / N;
}