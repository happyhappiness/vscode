void
MemBlob::appended(const size_type n)
{
    Must(willFit(n));
    size += n;
    ++Stats.append;
}