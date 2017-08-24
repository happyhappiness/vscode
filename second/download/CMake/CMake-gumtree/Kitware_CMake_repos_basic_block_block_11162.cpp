(cfdata->sum_extra_avail == 4) {
			cfdata->sum_calculated = cab_checksum_cfdata_4(
			    cfdata->sum_extra, 4, cfdata->sum_calculated);
			cfdata->sum_extra_avail = 0;
		}