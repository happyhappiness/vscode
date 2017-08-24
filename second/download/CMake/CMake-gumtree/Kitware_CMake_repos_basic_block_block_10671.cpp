(i = 0; i < f->numPackedStreams; i++) {
			if (parse_7zip_uint64(a, &(f->packedStreams[i])) < 0)
				return (-1);
			if (UMAX_ENTRY < f->packedStreams[i])
				return (-1);
		}