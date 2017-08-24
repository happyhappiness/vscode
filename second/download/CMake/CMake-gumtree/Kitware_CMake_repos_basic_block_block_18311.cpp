{
		rc->symbols[rc->count++]
				= RC_DIRECT_0 + ((value >> --bit_count) & 1);
	}