{
		/* Current folder does not have any CFDATA. */
		cfdata = &(cab->entry_cffolder->cfdata);
		cab->entry_cfdata = cfdata;
		memset(cfdata, 0, sizeof(*cfdata));
	}