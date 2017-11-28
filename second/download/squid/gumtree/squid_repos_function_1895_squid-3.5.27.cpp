unsigned int
StatHist::findBin(double v)
{

    v -= min_;      /* offset */

    if (v <= 0.0)       /* too small */
        return 0;

    unsigned int bin;
    double tmp_bin=floor(scale_ * val_in(v) + 0.5);

    if (tmp_bin < 0.0) // should not happen
        return 0;
    bin = static_cast <unsigned int>(tmp_bin);

    if (bin >= capacity_)   /* too big */
        bin = capacity_ - 1;

    return bin;
}