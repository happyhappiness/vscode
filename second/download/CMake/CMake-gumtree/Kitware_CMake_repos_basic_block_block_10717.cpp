(j = 0; j < folder->numOutStreams; j++) {
			if (parse_7zip_uint64(a, &(folder->unPackSize[j])) < 0)
				goto failed;
		}