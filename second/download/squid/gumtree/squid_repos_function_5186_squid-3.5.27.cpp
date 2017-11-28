bool
Rock::Rebuild::doneAll() const
{
    return loadingPos >= dbSlotLimit && validationPos >= dbSlotLimit &&
           AsyncJob::doneAll();
}