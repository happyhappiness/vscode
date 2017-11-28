static void
memBufAppend(MemBuf *mb, const char *buf, mb_size_t len)
{
    mb->append(buf, len);
}