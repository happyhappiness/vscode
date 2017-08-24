{
		/* Build and write out 8-byte trailer. */
		trailer[0] = (uint8_t)(data->crc)&0xff;
		trailer[1] = (uint8_t)(data->crc >> 8)&0xff;
		trailer[2] = (uint8_t)(data->crc >> 16)&0xff;
		trailer[3] = (uint8_t)(data->crc >> 24)&0xff;
		trailer[4] = (uint8_t)(data->total_in)&0xff;
		trailer[5] = (uint8_t)(data->total_in >> 8)&0xff;
		trailer[6] = (uint8_t)(data->total_in >> 16)&0xff;
		trailer[7] = (uint8_t)(data->total_in >> 24)&0xff;
		ret = __archive_write_filter(f->next_filter, trailer, 8);
	}