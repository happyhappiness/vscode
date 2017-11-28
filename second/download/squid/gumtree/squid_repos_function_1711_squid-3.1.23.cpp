static double
statHistVal(const StatHist * H, int bin)
{
    return H->val_out((double) bin / H->scale) + H->min;
}