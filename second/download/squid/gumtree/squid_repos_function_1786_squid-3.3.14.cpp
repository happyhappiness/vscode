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