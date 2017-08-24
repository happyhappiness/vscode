(mf->depth == 0) {
		if (is_bt)
			mf->depth = 16 + mf->nice_len / 2;
		else
			mf->depth = 4 + mf->nice_len / 4;
	}