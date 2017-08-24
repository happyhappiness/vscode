{
		// If the preset dictionary is bigger than the actual
		// dictionary, use only the tail.
		mf->write_pos = my_min(lz_options->preset_dict_size, mf->size);
		memcpy(mf->buffer, lz_options->preset_dict
				+ lz_options->preset_dict_size - mf->write_pos,
				mf->write_pos);
		mf->action = LZMA_SYNC_FLUSH;
		mf->skip(mf, mf->write_pos);
	}