void
DelayTagged::update(int incr)
{
    DelayTaggedUpdater updater(spec, incr);
    DelayTaggedUpdateVisitor visitor(&updater);
    buckets.visit(visitor);
    kickReads();
}