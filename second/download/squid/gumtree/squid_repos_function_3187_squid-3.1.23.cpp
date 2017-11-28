bool
mem_node::operator < (mem_node const & rhs) const
{
    return start() < rhs.start();
}