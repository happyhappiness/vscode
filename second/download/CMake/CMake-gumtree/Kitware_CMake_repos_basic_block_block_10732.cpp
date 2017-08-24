(--n >= 0) {
		unsigned i;
		for (i = 0; i < pairs; i++) {
			if (f->bindPairs[i].outIndex == (uint64_t)n)
				break;
		}
		if (i >= pairs)
			return (f->unPackSize[n]);
	}