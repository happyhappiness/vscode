void
ClassCBucket::update (DelaySpec const &rate, int incr)
{
    /* If we aren't active, don't try to update us ! */
    assert (rate.restore_bps != -1);

    for (unsigned int j = 0; j < individuals.size(); ++j)
        individuals.values[j].update (rate, incr);
}