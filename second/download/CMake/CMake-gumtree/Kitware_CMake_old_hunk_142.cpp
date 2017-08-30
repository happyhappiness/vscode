		archive_set_error(&a->archive, errno, "statvfs failed");

		return (ARCHIVE_FAILED);

	} else if (xr == 1) {

		/* Usuall come here unless NetBSD supports _PC_REC_XFER_ALIGN

		 * for pathconf() function. */

		t->current_filesystem->xfer_align = sfs.f_frsize;

		t->current_filesystem->max_xfer_size = -1;

