{
		/*
		 * Make MainStreamInfo.
		 */
		r = enc_uint64(a, kMainStreamsInfo);
		if (r < 0)
			return (r);
		r = make_streamsInfo(a, offset, pack_size, unpack_size,
		      codernum, coders, 1, 0);
		if (r < 0)
			return (r);
	}