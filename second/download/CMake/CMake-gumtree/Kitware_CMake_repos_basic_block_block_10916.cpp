{
			zip->uncompressed_buffer_size = minimum + 1023;
			zip->uncompressed_buffer_size &= ~0x3ff;
		}