void
MemBlob::append(const char *source, const size_type n)
{
    if (n > 0) { // appending zero bytes is allowed but only affects the stats
        Must(willFit(n));
        Must(source);
        memmove(mem + size, source, n);
        size += n;
    }
    ++Stats.append;
}