(outranges == NULL) {
					archive_set_error(&a->archive, ENOMEM,
					    "Couldn't allocate memory");
					exit_sts = ARCHIVE_FATAL;
					goto exit_setup_sparse;
				}