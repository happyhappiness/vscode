(cbytes > 0) {
			if (consumed_bytes < cbytes)
				cbytes = consumed_bytes;
			rbytes -= cbytes;
			cfdata->read_offset += (uint16_t)cbytes;
			cfdata->uncompressed_bytes_remaining -= (uint16_t)cbytes;
		}