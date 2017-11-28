int
DelayTagged::Id::bytesWanted (int min, int max) const
{
    return theBucket->theBucket.bytesWanted(min,max);
}