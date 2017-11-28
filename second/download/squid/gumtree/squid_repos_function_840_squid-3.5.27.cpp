DelayIdComposite::Pointer
DelayVector::id(CompositeSelectionDetails &details)
{
    return new Id(this, details);
}