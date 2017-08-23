{
#ifdef HAVE_ZLIB_H
			if (value == NULL ||
			    !(value[0] >= '0' && value[0] <= '9') ||
			    value[1] != '\0')
				goto invalid_value;
                	iso9660->zisofs.compression_level = value[0] - '0';
			iso9660->opt.compression_level = 1;
                	return (ARCHIVE_OK);
#else
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "Option ``%s'' "
			    "is not supported on this platform.", key);
			return (ARCHIVE_FATAL);
#endif
		}