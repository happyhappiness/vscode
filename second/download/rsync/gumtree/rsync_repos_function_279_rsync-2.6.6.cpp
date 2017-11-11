static int next_delayed_bit(int after)
{
	uint32 bits, mask;
	int i, ndx = after + 1;
	int slot = ndx / PER_SLOT_BITS;
	ndx %= PER_SLOT_BITS;

	mask = (1u << (ndx % 32)) - 1;
	for (i = ndx / 32; slot < delayed_slot_cnt; slot++, i = mask = 0) {
		if (!delayed_bits[slot])
			continue;
		for ( ; i < PER_SLOT_INTS; i++, mask = 0) {
			if (!(bits = delayed_bits[slot][i] & ~mask))
				continue;
			/* The xor magic figures out the lowest enabled bit in
			 * bits, and the switch quickly computes log2(bit). */
			switch (bits ^ (bits & (bits-1))) {
#define LOG2(n) case 1u << n: return slot*PER_SLOT_BITS + i*32 + n
			    LOG2(0);  LOG2(1);  LOG2(2);  LOG2(3);
			    LOG2(4);  LOG2(5);  LOG2(6);  LOG2(7);
			    LOG2(8);  LOG2(9);  LOG2(10); LOG2(11);
			    LOG2(12); LOG2(13); LOG2(14); LOG2(15);
			    LOG2(16); LOG2(17); LOG2(18); LOG2(19);
			    LOG2(20); LOG2(21); LOG2(22); LOG2(23);
			    LOG2(24); LOG2(25); LOG2(26); LOG2(27);
			    LOG2(28); LOG2(29); LOG2(30); LOG2(31);
			}
			return -1; /* impossible... */
		}
	}

	return -1;
}