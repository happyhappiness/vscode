{
		ss->unpackSizes = calloc(unpack_streams,
		    sizeof(*ss->unpackSizes));
		ss->digestsDefined = calloc(unpack_streams,
		    sizeof(*ss->digestsDefined));
		ss->digests = calloc(unpack_streams,
		    sizeof(*ss->digests));
		if (ss->unpackSizes == NULL || ss->digestsDefined == NULL ||
		    ss->digests == NULL)
			return (-1);
	}