void
DelayUser::update(int incr)
{
    DelayUserUpdater updater(spec, incr);
    buckets.head->walk (DelayUserUpdateWalkee, &updater);
}