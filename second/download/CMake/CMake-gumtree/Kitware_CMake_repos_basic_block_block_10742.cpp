{
		struct _7z_digests tmpDigests;
		unsigned char *digestsDefined = ss->digestsDefined;
		uint32_t * digests = ss->digests;
		int di = 0;

		memset(&tmpDigests, 0, sizeof(tmpDigests));
		if (read_Digests(a, &(tmpDigests), numDigests) < 0) {
			free_Digest(&tmpDigests);
			return (-1);
		}
		for (i = 0; i < numFolders; i++) {
			if (f[i].numUnpackStreams == 1 && f[i].digest_defined) {
				*digestsDefined++ = 1;
				*digests++ = f[i].digest;
			} else {
				unsigned j;

				for (j = 0; j < f[i].numUnpackStreams;
				    j++, di++) {
					*digestsDefined++ =
					    tmpDigests.defineds[di];
					*digests++ =
					    tmpDigests.digests[di];
				}
			}
		}
		free_Digest(&tmpDigests);
		if ((p = header_bytes(a, 1)) == NULL)
			return (-1);
		type = *p;
	}