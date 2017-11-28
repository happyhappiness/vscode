void
DelayBucket::bytesIn(int qty)
{
    level() -= qty;
}