{
		unsigned pack;
		uint64_t sum;

		if (f[i].numUnpackStreams == 0)
			continue;

		sum = 0;
		if (type == kSize) {
			for (pack = 1; pack < f[i].numUnpackStreams; pack++) {
				if (parse_7zip_uint64(a, usizes) < 0)
					return (-1);
				sum += *usizes++;
			}
		}
		*usizes++ = folder_uncompressed_size(&f[i]) - sum;
	}