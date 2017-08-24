(*p == kPackInfo) {
		uint64_t packPos;

		if (read_PackInfo(a, &(si->pi)) < 0)
			return (-1);

		if (si->pi.positions == NULL || si->pi.sizes == NULL)
			return (-1);
		/*
		 * Calculate packed stream positions.
		 */
		packPos = si->pi.pos;
		for (i = 0; i < si->pi.numPackStreams; i++) {
			si->pi.positions[i] = packPos;
			packPos += si->pi.sizes[i];
			if (packPos > zip->header_offset)
				return (-1);
		}
		if ((p = header_bytes(a, 1)) == NULL)
			return (-1);
	}