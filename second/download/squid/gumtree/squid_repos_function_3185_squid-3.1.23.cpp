bool
mem_node::contains (int64_t const &location) const
{
    if (start() <= location && end() > location)
        return true;

    return false;
}