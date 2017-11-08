static enum input_source istream_source(const unsigned char *sha1,
					enum object_type *type,
					struct object_info *oi)
{
	unsigned long size;
	int status;

	oi->typep = type;
	oi->sizep = &size;
	status = sha1_object_info_extended(sha1, oi, 0);
	if (status < 0)
		return stream_error;

	switch (oi->whence) {
	case OI_LOOSE:
		return loose;
	case OI_PACKED:
		if (!oi->u.packed.is_delta && big_file_threshold < size)
			return pack_non_delta;
		/* fallthru */
	default:
		return incore;
	}
}