{
		cfdata->sum_calculated =
		    cab_checksum_cfdata(cfdata->sum_extra,
		       cfdata->sum_extra_avail, cfdata->sum_calculated);
		cfdata->sum_extra_avail = 0;
	}