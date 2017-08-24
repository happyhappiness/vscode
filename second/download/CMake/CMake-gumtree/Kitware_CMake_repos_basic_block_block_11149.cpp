(cab->entry_unconsumed) {
		/* Consume as much as the compressor actually used. */
		r = (int)cab_consume_cfdata(a, cab->entry_unconsumed);
		cab->entry_unconsumed = 0;
		if (r < 0)
			return (r);
	}