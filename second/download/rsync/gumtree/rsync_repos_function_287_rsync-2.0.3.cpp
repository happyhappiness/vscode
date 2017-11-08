local int inflate_packet_flush(s)
    inflate_blocks_statef *s;
{
    if (s->mode != LENS)
	return Z_DATA_ERROR;
    s->mode = TYPE;
    return Z_OK;
}