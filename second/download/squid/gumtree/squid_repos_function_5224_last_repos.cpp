bool
Client::doneWithAdaptation() const
{
    return !adaptationAccessCheckPending &&
           !virginBodyDestination && !adaptedHeadSource && !adaptedBodySource;
}