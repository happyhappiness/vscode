{
		r = deflateInit(&(iso9660->zisofs.stream),
		    iso9660->zisofs.compression_level);
		iso9660->zisofs.stream_valid = 1;
	}