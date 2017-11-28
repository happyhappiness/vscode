void
DelayPools::registerForUpdates(Updateable *anObject)
{
    /* Assume no doubles */
    toUpdate.push_back(anObject);
}