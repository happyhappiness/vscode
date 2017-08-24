{
		/* ASCII cpio archive (odc, POSIX.1) */
		cpio->read_header = header_odc;
		bid += 48;
		/*
		 * XXX TODO:  More verification; Could check that only octal
		 * digits appear in appropriate header locations. XXX
		 */
	}