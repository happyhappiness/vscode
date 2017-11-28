void
DelayTaggedUpdateWalkee(DelayTaggedBucket::Pointer const &current, void *state)
{
    DelayTaggedUpdater *t = (DelayTaggedUpdater *)state;
    /* This doesn't change the value of the DelayTaggedBucket, so is safe */
    const_cast<DelayTaggedBucket *>(current.getRaw())->theBucket.update(t->spec, t->incr);
}