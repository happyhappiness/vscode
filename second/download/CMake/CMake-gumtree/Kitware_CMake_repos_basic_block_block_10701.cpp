{
		size_t codec_size;
		int simple, attr;

		if ((p = header_bytes(a, 1)) == NULL)
			return (-1);
		/*
		 * 0:3 CodecIdSize
		 * 4:  0 - IsSimple
		 *     1 - Is not Simple
		 * 5:  0 - No Attributes
		 *     1 - There are Attributes;
		 * 7:  Must be zero.
		 */
		codec_size = *p & 0xf;
		simple = (*p & 0x10)?0:1;
		attr = *p & 0x20;
		if (*p & 0x80)
			return (-1);/* Not supported. */

		/*
		 * Read Decompression Method IDs.
		 */
		if ((p = header_bytes(a, codec_size)) == NULL)
			return (-1);

		f->coders[i].codec = decode_codec_id(p, codec_size);

		if (simple) {
			f->coders[i].numInStreams = 1;
			f->coders[i].numOutStreams = 1;
		} else {
			if (parse_7zip_uint64(
			    a, &(f->coders[i].numInStreams)) < 0)
				return (-1);
			if (UMAX_ENTRY < f->coders[i].numInStreams)
				return (-1);
			if (parse_7zip_uint64(
			    a, &(f->coders[i].numOutStreams)) < 0)
				return (-1);
			if (UMAX_ENTRY < f->coders[i].numOutStreams)
				return (-1);
		}

		if (attr) {
			if (parse_7zip_uint64(
			    a, &(f->coders[i].propertiesSize)) < 0)
				return (-1);
			if ((p = header_bytes(
			    a, (size_t)f->coders[i].propertiesSize)) == NULL)
				return (-1);
			f->coders[i].properties =
			    malloc((size_t)f->coders[i].propertiesSize);
			if (f->coders[i].properties == NULL)
				return (-1);
			memcpy(f->coders[i].properties, p,
			    (size_t)f->coders[i].propertiesSize);
		}

		numInStreamsTotal += f->coders[i].numInStreams;
		numOutStreamsTotal += f->coders[i].numOutStreams;
	}