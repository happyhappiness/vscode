void
mem_hdr::dump() const
{
    debugs(20, 1, "mem_hdr: " << (void *)this << " nodes.start() " << nodes.start());
    debugs(20, 1, "mem_hdr: " << (void *)this << " nodes.finish() " << nodes.finish());
}