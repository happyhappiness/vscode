static int
cab_checksum_finish(struct archive_read *a)
{
	struct cab *cab = (struct cab *)(a->format->data);
	struct cfdata *cfdata = cab->entry_cfdata;
	int l;

	/* Do not need to compute a sum. */
	if (cfdata->sum == 0)
		return (ARCHIVE_OK);

	/*
	 * Calculate the sum of remaining CFDATA.
	 */
	if (cfdata->sum_extra_avail) {
		cfdata->sum_calculated =
		    cab_checksum_cfdata(cfdata->sum_extra,
		       cfdata->sum_extra_avail, cfdata->sum_calculated);
		cfdata->sum_extra_avail = 0;
	}

	l = 4;
	if (cab->cfheader.flags & RESERVE_PRESENT)
		l += cab->cfheader.cfdata;
	cfdata->sum_calculated = cab_checksum_cfdata(
	    cfdata->memimage + CFDATA_cbData, l, cfdata->sum_calculated);
	if (cfdata->sum_calculated != cfdata->sum) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Checksum error CFDATA[%d] %x:%x in %d bytes",
		    cab->entry_cffolder->cfdata_index -1,
		    cfdata->sum, cfdata->sum_calculated,
		    cfdata->compressed_size);
		return (ARCHIVE_FAILED);
	}
	return (ARCHIVE_OK);
}