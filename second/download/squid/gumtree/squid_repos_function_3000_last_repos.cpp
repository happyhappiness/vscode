void
clientPackTermBound(String boundary, MemBuf *mb)
{
    mb->appendf("\r\n--" SQUIDSTRINGPH "--\r\n", SQUIDSTRINGPRINT(boundary));
    debugs(33, 6, "buf offset: " << mb->size);
}