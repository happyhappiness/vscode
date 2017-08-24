{
		d = cab->uncompressed_buffer + cfdata->read_offset;
		*avail = uavail - cfdata->read_offset;
		return (d);
	}