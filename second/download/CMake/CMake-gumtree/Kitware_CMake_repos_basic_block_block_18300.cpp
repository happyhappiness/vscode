{
		options->mode = LZMA_MODE_NORMAL;
		options->mf = LZMA_MF_BT4;
		if (level == 3 || level == 5) {
			options->nice_len = 192;
			options->depth = 0;
		} else {
			options->nice_len = 273;
			options->depth = 512;
		}
	}