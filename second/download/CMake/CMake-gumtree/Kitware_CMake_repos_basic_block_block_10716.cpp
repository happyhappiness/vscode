(i = 0; i < ci->numFolders; i++) {
		struct _7z_folder *folder = &(ci->folders[i]);
		unsigned j;

		folder->unPackSize =
		    calloc((size_t)folder->numOutStreams, sizeof(*folder->unPackSize));
		if (folder->unPackSize == NULL)
			goto failed;
		for (j = 0; j < folder->numOutStreams; j++) {
			if (parse_7zip_uint64(a, &(folder->unPackSize[j])) < 0)
				goto failed;
		}
	}