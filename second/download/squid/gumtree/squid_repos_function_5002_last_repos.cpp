bool
Rock::Rebuild::doneLoading() const
{
    return loadingPos >= dbSlotLimit;
}