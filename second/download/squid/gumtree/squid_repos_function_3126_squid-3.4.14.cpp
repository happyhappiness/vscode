int
isPowTen(int count)
{
    double x = log(static_cast<double>(count)) / log(10.0);

    if (0.0 != x - (double) (int) x)
        return 0;

    return 1;
}