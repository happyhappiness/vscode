(*p == kUnPackInfo) {
		uint32_t packIndex;
		struct _7z_folder *f;

		if (read_CodersInfo(a, &(si->ci)) < 0)
			return (-1);

		/*
		 * Calculate packed stream indexes.
		 */
		packIndex = 0;
		f = si->ci.folders;
		for (i = 0; i < si->ci.numFolders; i++) {
			f[i].packIndex = packIndex;
			packIndex += (uint32_t)f[i].numPackedStreams;
			if (packIndex > si->pi.numPackStreams)
				return (-1);
		}
		if ((p = header_bytes(a, 1)) == NULL)
			return (-1);
	}