static void set_delayed_bit(int ndx)
{
	int slot = ndx / PER_SLOT_BITS;
	ndx %= PER_SLOT_BITS;

	if (!delayed_bits[slot]) {
		if (!(delayed_bits[slot] = (uint32*)calloc(PER_SLOT_INTS, 4)))
			out_of_memory("set_delayed_bit");
	}

	delayed_bits[slot][ndx/32] |= 1u << (ndx % 32);
}