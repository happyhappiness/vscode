void
mem_hdr::debugDump() const
{
    debugs (19, 0, "mem_hdr::debugDump: lowest offset: " << lowestOffset() << " highest offset + 1: " << endOffset() << ".");
    std::ostringstream result;
    PointerPrinter<mem_node *> foo(result, " - ");
    getNodes().visit(foo);
    debugs (19, 0, "mem_hdr::debugDump: Current available data is: " << result.str() << ".");
}