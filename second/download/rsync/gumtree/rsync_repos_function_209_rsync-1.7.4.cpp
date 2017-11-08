int inflateIncomp(z)
z_stream *z;
{
    if (z->state->mode != BLOCKS)
	return Z_DATA_ERROR;
    return inflate_addhistory(z->state->blocks, z);
}