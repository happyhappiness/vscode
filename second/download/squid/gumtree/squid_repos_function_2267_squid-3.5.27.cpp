void
mem_hdr::dump() const
{
    debugs(20, DBG_IMPORTANT, "mem_hdr: " << (void *)this << " nodes.start() " << nodes.start());
    debugs(20, DBG_IMPORTANT, "mem_hdr: " << (void *)this << " nodes.finish() " << nodes.finish());
}