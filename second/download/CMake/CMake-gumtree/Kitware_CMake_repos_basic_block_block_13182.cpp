{
			BZ2_bzDecompressEnd(&(xar->bzstream));
			xar->bzstream_valid = 0;
		}