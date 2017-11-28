double
StatHist::val(unsigned int bin) const
{
    return val_out((double) bin / scale_) + min_;
}