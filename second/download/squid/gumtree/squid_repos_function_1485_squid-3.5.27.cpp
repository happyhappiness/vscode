void
DelayUser::update(int incr)
{
    DelayUserUpdater updater(spec, incr);
    DelayUserUpdateVisitor visitor(&updater);
    buckets.visit(visitor);
}