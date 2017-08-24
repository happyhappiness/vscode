(cfdata->compressed_size == 0 ||
		    cfdata->compressed_size > (0x8000+6144))
			goto invalid;