r = inflateInit2(&zip->stream,
			    -15 /* Don't check for zlib header */)