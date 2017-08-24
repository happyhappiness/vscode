(cfdata->compressed_bytes_remaining == 0) {
			err = cab_checksum_finish(a);
			if (err < 0)
				return (err);
		}