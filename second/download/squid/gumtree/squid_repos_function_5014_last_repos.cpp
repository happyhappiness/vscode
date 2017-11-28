void
Rock::Rebuild::finalizeOrFree(const sfileno fileNo, LoadingEntry &le)
{
    try {
        finalizeOrThrow(fileNo, le);
    } catch (const std::exception &ex) {
        freeBadEntry(fileNo, ex.what());
    }
}