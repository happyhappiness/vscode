{
	struct cab *cab = (struct cab *)(a->format->data);
	struct cfdata *cfdata;
	int64_t cbytes, rbytes;
	int err;

	cfdata = cab->entry_cfdata;
	rbytes = consumed_bytes;
	if (cab->entry_cffolder->comptype == COMPTYPE_NONE) {
		if (consumed_bytes < cfdata->unconsumed)
			cbytes = consumed_bytes;
		else
			cbytes = cfdata->unconsumed;
		rbytes -= cbytes; 
		cfdata->read_offset += (uint16_t)cbytes;
		cfdata->uncompressed_bytes_remaining -= (uint16_t)cbytes;
		cfdata->unconsumed -= cbytes;
	} else {
		cbytes = cfdata->uncompressed_avail - cfdata->read_offset;
		if (cbytes > 0) {
			if (consumed_bytes < cbytes)
				cbytes = consumed_bytes;
			rbytes -= cbytes;
			cfdata->read_offset += (uint16_t)cbytes;
			cfdata->uncompressed_bytes_remaining -= (uint16_t)cbytes;
		}

		if (cfdata->unconsumed) {
			cbytes = cfdata->unconsumed;
			cfdata->unconsumed = 0;
		} else
			cbytes = 0;
	}
	if (cbytes) {
		/* Compute the sum. */
		cab_checksum_update(a, (size_t)cbytes);

		/* Consume as much as the compressor actually used. */
		__archive_read_consume(a, cbytes);
		cab->cab_offset += cbytes;
		cfdata->compressed_bytes_remaining -= (uint16_t)cbytes;
		if (cfdata->compressed_bytes_remaining == 0) {
			err = cab_checksum_finish(a);
			if (err < 0)
				return (err);
		}
	}
	return (rbytes);
}