double
drand48(void)
{
    static double two16m = 1.0 / (1L << N);
    next();
    return (two16m * (two16m * (two16m * x[0] + x[1]) + x[2]));
}