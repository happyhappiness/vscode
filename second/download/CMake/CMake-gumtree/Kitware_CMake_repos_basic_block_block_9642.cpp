{
			if (errno == ENXIO) {
				off_e = lseek(*fd, 0, SEEK_END);
				if (off_e != (off_t)-1)
					break;/* no more data */
			}
			archive_set_error(&a->archive, errno,
			    "lseek(SEEK_DATA) failed");
			exit_sts = ARCHIVE_FAILED;
			goto exit_setup_sparse;
		}