(memcmp("070727", p, 6) == 0 && is_afio_large(p, bytes)) {
			a->archive.archive_format = ARCHIVE_FORMAT_CPIO_AFIO_LARGE;
			return (ARCHIVE_OK);
		}