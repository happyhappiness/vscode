
    if (I >= J)
        return 0.0;

    f = (h - a) / (b - a);

    K = (unsigned int) floor(f * (double) (J - I) + I);

    return val(K);
}

static void
statHistBinDumper(StoreEntry * sentry, int idx, double val, double size, int count)
{
    if (count)
        storeAppendPrintf(sentry, "\t%3d/%f\t%d\t%f\n",
                          idx, val, count, count / size);
}

void
StatHist::dump(StoreEntry * sentry, StatHistBinDumper * bd) const
{
    double left_border = min_;

    if (!bd)
        bd = statHistBinDumper;

    for (unsigned int i = 0; i < capacity_; ++i) {
        const double right_border = val(i + 1);
        assert(right_border - left_border > 0.0);
        bd(sentry, i, left_border, right_border - left_border, bins[i]);
        left_border = right_border;
    }
}

/* log based histogram */
double
Math::Log(double x)
{
    assert((x + 1.0) >= 0.0);
    return log(x + 1.0);
}

double
Math::Exp(double x)
{
    return exp(x) - 1.0;
}

void
StatHist::logInit(unsigned int capacity, double min, double max)
{
    init(capacity, Math::Log, Math::Exp, min, max);
}

/* linear histogram for enums */
/* we want to be have [-1,last_enum+1] range to track out of range enums */
double
Math::Null(double x)
{
    return x;
}

void
StatHist::enumInit(unsigned int last_enum)
{
    init(last_enum + 3, Math::Null, Math::Null, -1.0, (2.0 + last_enum));
}

void
statHistEnumDumper(StoreEntry * sentry, int idx, double val, double size, int count)
{
    if (count)
        storeAppendPrintf(sentry, "%2d\t %5d\t %5d\n",
                          idx, (int) val, count);
}

void
statHistIntDumper(StoreEntry * sentry, int idx, double val, double size, int count)
{
    if (count)
        storeAppendPrintf(sentry, "%9d\t%9d\n", (int) val, count);
}
