void
StatHist::init(unsigned int newCapacity, hbase_f * val_in_, hbase_f * val_out_, double newMin, double newMax)
{
    /* check before we divide to get scale_ */
    assert(val_in_(newMax - newMin) > 0);
    min_ = newMin;
    max_ = newMax;
    capacity_ = newCapacity;
    val_in = val_in_;
    val_out = val_out_;
    bins = static_cast<bins_type *>(xcalloc(capacity_, sizeof(bins_type)));
    scale_ = capacity_ / val_in(max_ - min_);
}