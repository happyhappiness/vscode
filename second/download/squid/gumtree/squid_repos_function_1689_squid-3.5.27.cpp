int
Aggregate::AggregateId::bytesWanted (int min, int max) const
{
    return theAggregate->theBucket.bytesWanted(min, max);
}