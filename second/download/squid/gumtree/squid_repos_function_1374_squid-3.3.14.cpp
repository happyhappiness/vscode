void
DelayUserUpdateWalkee(DelayUserBucket::Pointer const &current, void *state)
{
    DelayUserUpdater *t = (DelayUserUpdater *)state;
    /* This doesn't change the value of the DelayUserBucket, so is safe */
    const_cast<DelayUserBucket *>(current.getRaw())->theBucket.update(t->spec, t->incr);
}