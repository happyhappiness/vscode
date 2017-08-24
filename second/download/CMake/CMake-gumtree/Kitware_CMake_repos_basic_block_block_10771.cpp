(*p == kSubStreamsInfo) {
		if (read_SubStreamsInfo(a, &(si->ss),
		    si->ci.folders, (size_t)si->ci.numFolders) < 0)
			return (-1);
		if ((p = header_bytes(a, 1)) == NULL)
			return (-1);
	}