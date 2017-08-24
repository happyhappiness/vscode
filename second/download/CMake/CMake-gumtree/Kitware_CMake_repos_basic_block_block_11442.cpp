{
		/* afio large ASCII cpio archive */
		cpio->read_header = header_odc;
		bid += 48;
		/*
		 * XXX TODO:  More verification; Could check that almost hex
		 * digits appear in appropriate header locations. XXX
		 */
	}