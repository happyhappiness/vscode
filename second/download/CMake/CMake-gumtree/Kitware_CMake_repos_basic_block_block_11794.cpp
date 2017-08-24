{
		/* paged zlib */
		file->pz = 1;
		file->pz_log2_bs = data[3];
		file->pz_uncompressed_size = archive_le32dec(&data[4]);
	}