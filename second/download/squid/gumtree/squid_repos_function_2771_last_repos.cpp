bool
mem_node::canAccept (int64_t const &location) const
{
    if (location == end() && space() > 0)
        return true;

    return false;
}