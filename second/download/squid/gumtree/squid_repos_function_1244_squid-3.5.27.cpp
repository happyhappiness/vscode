void
DelayBucket::update(DelaySpec const &rate, int incr)
{
    if (rate.restore_bps != -1 &&
            (level() += rate.restore_bps * incr) > rate.max_bytes)
        level() = rate.max_bytes;
}