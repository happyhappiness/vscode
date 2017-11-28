void
Aggregate::update(int incr)
{
    theBucket.update(*rate(), incr);
    kickReads();
}