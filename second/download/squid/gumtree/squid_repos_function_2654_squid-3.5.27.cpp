void
kb_incr(kb_t * k, size_t v)
{
    k->bytes += v;
    k->kb += (k->bytes >> 10);
    k->bytes &= 0x3FF;
}