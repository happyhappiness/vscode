DelayIdComposite::Pointer

DelayTagged::id(CompositePoolNode::CompositeSelectionDetails &details)
{
    if (!details.tag.size())
        return new NullDelayId;

    return new Id(this, details.tag);
}