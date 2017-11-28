void
ClassCHostPool::update(int incr)
{
    if (rate()->restore_bps == -1)
        return;

    for (unsigned int i = 0; i< buckets.size(); ++i)
        buckets.values[i].update (*rate(), incr);
}