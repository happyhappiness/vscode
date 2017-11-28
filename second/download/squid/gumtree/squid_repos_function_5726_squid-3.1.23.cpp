void
gb_flush(gb_t * g)
{
    g->gb += (g->bytes >> 30);
    g->bytes &= (1 << 30) - 1;
}