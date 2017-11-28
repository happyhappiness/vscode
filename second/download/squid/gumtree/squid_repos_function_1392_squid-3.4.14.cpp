DelayIdComposite::Pointer
DelayUser::id(CompositePoolNode::CompositeSelectionDetails &details)
{
    if (!details.user || !details.user->user() || !details.user->user()->username())
        return new NullDelayId;

    debugs(77, 3, HERE << "Adding a slow-down for User '" << details.user->user()->username() << "'");
    return new Id(this, details.user->user());
}