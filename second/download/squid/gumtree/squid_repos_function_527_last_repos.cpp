int64_t
Transients::maxObjectSize() const
{
    // Squid currently does not limit the size of a transient object
    return std::numeric_limits<uint64_t>::max();
}