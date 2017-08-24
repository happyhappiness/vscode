(i = 0; i < numFolders; i++) {
			if (parse_7zip_uint64(a, &(f[i].numUnpackStreams)) < 0)
				return (-1);
			if (UMAX_ENTRY < f[i].numUnpackStreams)
				return (-1);
			if (unpack_streams > SIZE_MAX - UMAX_ENTRY) {
				return (-1);
			}
			unpack_streams += (size_t)f[i].numUnpackStreams;
		}