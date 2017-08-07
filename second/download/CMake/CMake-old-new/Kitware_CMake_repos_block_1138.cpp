{
#if HAVE_ICONV
			archive_set_error(a, ARCHIVE_ERRNO_MISC,
			    "iconv_open failed : Cannot handle ``%s''",
			    (flag & SCONV_TO_CHARSET)?tc:fc);
#else
			archive_set_error(a, ARCHIVE_ERRNO_MISC,
			    "A character-set conversion not fully supported "
			    "on this platform");
#endif
		}