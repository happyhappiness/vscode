(cab->entry_cffolder->cfdata_index <
	    cab->entry_cffolder->cfdata_count) {
		r = inflateReset(&cab->stream);
		if (r != Z_OK)
			goto zlibfailed;
		r = inflateSetDictionary(&cab->stream,
		    cab->uncompressed_buffer, cfdata->uncompressed_size);
		if (r != Z_OK)
			goto zlibfailed;
	}