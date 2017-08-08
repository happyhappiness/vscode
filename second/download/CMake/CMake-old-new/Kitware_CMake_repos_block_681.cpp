{
#ifdef HAVE_ZLIB_H
				iso9660->opt.zisofs = OPT_ZISOFS_DIRECT;
#else
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "``zisofs'' "
				    "is not supported on this platform.");
				return (ARCHIVE_FATAL);
#endif
			}