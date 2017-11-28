void
ClassCBucket::initHostIndex (DelaySpec &rate, unsigned char index, unsigned char host)
{
    assert (!individualUsed(index));

    unsigned char const newIndex = individuals.insert (host);

    /* give the bucket a default value */
    individuals.values[newIndex].init (rate);
}