{
		time_t t = time(NULL);
		data->compressed[4] = (uint8_t)(t)&0xff;  /* Timestamp */
		data->compressed[5] = (uint8_t)(t>>8)&0xff;
		data->compressed[6] = (uint8_t)(t>>16)&0xff;
		data->compressed[7] = (uint8_t)(t>>24)&0xff;
	}