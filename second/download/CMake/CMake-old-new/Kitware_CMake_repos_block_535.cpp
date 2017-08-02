{
				const char *detail = NULL;
				int err = ARCHIVE_ERRNO_MISC;
				switch (ret) {
				case BZ_PARAM_ERROR:
					detail = "invalid setup parameter";
					break;
				case BZ_MEM_ERROR:
					err = ENOMEM;
					detail = "out of memory";
					break;
				case BZ_CONFIG_ERROR:
					detail = "mis-compiled library";
					break;
				}
				archive_set_error(&self->archive->archive, err,
				    "Internal error initializing decompressor%s%s",
				    detail == NULL ? "" : ": ",
				    detail);
				return (ARCHIVE_FATAL);
			}