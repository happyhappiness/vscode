void
Ipc::Mem::NotePageNeed(const int purpose, const int count)
{
    Must(0 <= purpose && purpose <= PageId::maxPurpose);
    Must(count >= 0);
    TheLimits[purpose] += count;
}