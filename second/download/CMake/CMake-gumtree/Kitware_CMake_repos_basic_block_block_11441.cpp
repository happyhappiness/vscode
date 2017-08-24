{
		/* ASCII cpio archive (SVR4 without CRC) */
		cpio->read_header = header_newc;
		bid += 48;
		/*
		 * XXX TODO:  More verification; Could check that only hex
		 * digits appear in appropriate header locations. XXX
		 */
	}