static void init_delayed_bits(int max_ndx)
{
	delayed_slot_cnt = (max_ndx + PER_SLOT_BITS - 1) / PER_SLOT_BITS;

	if (!(delayed_bits = (uint32**)calloc(delayed_slot_cnt, sizeof (uint32*))))
		out_of_memory("set_delayed_bit");
}