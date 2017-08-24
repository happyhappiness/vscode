{
	struct cab *cab = (struct cab *)(a->format->data);
	struct cfdata *cfdata = cab->entry_cfdata;
	const unsigned char *p;
	size_t sumbytes;

	if (cfdata->sum == 0 || cfdata->sum_ptr == NULL)
		return;
	/*
	 * Calculate the sum of this CFDATA.
	 * Make sure CFDATA must be calculated in four bytes.
	 */
	p = cfdata->sum_ptr;
	sumbytes = bytes;
	if (cfdata->sum_extra_avail) {
		while (cfdata->sum_extra_avail < 4 && sumbytes > 0) {
			cfdata->sum_extra[
			    cfdata->sum_extra_avail++] = *p++;
			sumbytes--;
		}
		if (cfdata->sum_extra_avail == 4) {
			cfdata->sum_calculated = cab_checksum_cfdata_4(
			    cfdata->sum_extra, 4, cfdata->sum_calculated);
			cfdata->sum_extra_avail = 0;
		}
	}
	if (sumbytes) {
		int odd = sumbytes & 3;
		if (sumbytes - odd > 0)
			cfdata->sum_calculated = cab_checksum_cfdata_4(
			    p, sumbytes - odd, cfdata->sum_calculated);
		if (odd)
			memcpy(cfdata->sum_extra, p + sumbytes - odd, odd);
		cfdata->sum_extra_avail = odd;
	}
	cfdata->sum_ptr = NULL;
}