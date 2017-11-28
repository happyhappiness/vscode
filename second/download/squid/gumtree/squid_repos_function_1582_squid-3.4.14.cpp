void
Aggregate::AggregateId::bytesIn(int qty)
{
    theAggregate->theBucket.bytesIn(qty);
    theAggregate->kickReads();
}