{
		int odd = sumbytes & 3;
		if (sumbytes - odd > 0)
			cfdata->sum_calculated = cab_checksum_cfdata_4(
			    p, sumbytes - odd, cfdata->sum_calculated);
		if (odd)
			memcpy(cfdata->sum_extra, p + sumbytes - odd, odd);
		cfdata->sum_extra_avail = odd;
	}