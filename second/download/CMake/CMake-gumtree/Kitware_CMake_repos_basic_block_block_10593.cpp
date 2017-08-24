{
			BZ2_bzDecompressEnd(&(zip->bzstream));
			zip->bzstream_valid = 0;
		}