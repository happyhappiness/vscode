Rock::LoadingEntry
Rock::Rebuild::loadingEntry(const sfileno fileNo)
{
    Must(0 <= fileNo && fileNo < dbEntryLimit);
    return LoadingEntry(fileNo, *parts);
}