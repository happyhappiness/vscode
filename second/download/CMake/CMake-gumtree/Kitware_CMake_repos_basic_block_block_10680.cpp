(f->numPackedStreams == 1) {
		for (i = 0; i < numInStreamsTotal; i++) {
			unsigned j;
			for (j = 0; j < f->numBindPairs; j++) {
				if (f->bindPairs[j].inIndex == i)
					break;
			}
			if (j == f->numBindPairs)
				break;
		}
		if (i == numInStreamsTotal)
			return (-1);
		f->packedStreams[0] = i;
	} else {
		for (i = 0; i < f->numPackedStreams; i++) {
			if (parse_7zip_uint64(a, &(f->packedStreams[i])) < 0)
				return (-1);
			if (UMAX_ENTRY < f->packedStreams[i])
				return (-1);
		}
	}