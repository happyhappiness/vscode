struct bitbag *bitbag_create(int max_ndx)
{
	struct bitbag *bb = new(struct bitbag);
	bb->slot_cnt = (max_ndx + BB_PER_SLOT_BITS - 1) / BB_PER_SLOT_BITS;

	if (!(bb->bits = (uint32**)calloc(bb->slot_cnt, sizeof (uint32*))))
		out_of_memory("bitbag_create");

	return bb;
}