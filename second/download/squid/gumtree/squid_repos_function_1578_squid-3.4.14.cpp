DelayIdComposite::Pointer
Aggregate::id(CompositeSelectionDetails &details)
{
    if (rate()->restore_bps != -1)
        return new AggregateId (this);
    else
        return new NullDelayId;
}