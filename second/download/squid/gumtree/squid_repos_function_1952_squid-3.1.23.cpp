void
DelayTagged::update(int incr)
{
    DelayTaggedUpdater updater(spec, incr);
    buckets.head->walk (DelayTaggedUpdateWalkee, &updater);
    kickReads();
}