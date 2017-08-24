{
		unsigned order;
		uint32_t msize;

		if (zip->ppmd7_valid) {
			__archive_ppmd7_functions.Ppmd7_Free(
			    &zip->ppmd7_context, &g_szalloc);
			zip->ppmd7_valid = 0;
		}

		if (coder1->propertiesSize < 5) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Malformed PPMd parameter");
			return (ARCHIVE_FAILED);
		}
		order = coder1->properties[0];
		msize = archive_le32dec(&(coder1->properties[1]));
		if (order < PPMD7_MIN_ORDER || order > PPMD7_MAX_ORDER ||
		    msize < PPMD7_MIN_MEM_SIZE || msize > PPMD7_MAX_MEM_SIZE) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Malformed PPMd parameter");
			return (ARCHIVE_FAILED);
		}
		__archive_ppmd7_functions.Ppmd7_Construct(&zip->ppmd7_context);
		r = __archive_ppmd7_functions.Ppmd7_Alloc(
			&zip->ppmd7_context, msize, &g_szalloc);
		if (r == 0) {
			archive_set_error(&a->archive, ENOMEM,
			    "Coludn't allocate memory for PPMd");
			return (ARCHIVE_FATAL);
		}
		__archive_ppmd7_functions.Ppmd7_Init(
			&zip->ppmd7_context, order);
		__archive_ppmd7_functions.Ppmd7z_RangeDec_CreateVTable(
			&zip->range_dec);
		zip->ppmd7_valid = 1;
		zip->ppmd7_stat = 0;
		zip->ppstream.overconsumed = 0;
		zip->ppstream.total_in = 0;
		zip->ppstream.total_out = 0;
		break;
	}