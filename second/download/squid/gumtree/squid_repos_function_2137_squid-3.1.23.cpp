bool
ServerStateData::doneWithAdaptation() const
{
    return !adaptationAccessCheckPending &&
           !virginBodyDestination && !adaptedHeadSource && !adaptedBodySource;
}