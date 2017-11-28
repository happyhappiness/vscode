void
statHistDump(const StatHist * H, StoreEntry * sentry, StatHistBinDumper * bd)
{
    int i;
    double left_border = H->min;

    if (!bd)
        bd = statHistBinDumper;

    for (i = 0; i < H->capacity; i++) {
        const double right_border = statHistVal(H, i + 1);
        assert(right_border - left_border > 0.0);
        bd(sentry, i, left_border, right_border - left_border, H->bins[i]);
        left_border = right_border;
    }
}