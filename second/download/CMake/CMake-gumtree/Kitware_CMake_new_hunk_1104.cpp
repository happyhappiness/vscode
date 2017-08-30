			return ARCHIVE_FATAL;

		}



		sconv = zip->sconv;

		if (sconv == NULL && (zip->entry->flags & ZIP_UTF8_NAME))

			sconv = zip->sconv_utf8;

		if (sconv == NULL)

			sconv = zip->sconv_default;

		if (archive_entry_copy_symlink_l(entry, p, linkname_length,

		    sconv) != 0) {

			if (errno != ENOMEM && sconv == zip->sconv_utf8 &&

			    (zip->entry->flags & ZIP_UTF8_NAME))

			    archive_entry_copy_symlink_l(entry, p,

				linkname_length, NULL);

			if (errno == ENOMEM) {

				archive_set_error(&a->archive, ENOMEM,

				    "Can't allocate memory for Symlink");

				return (ARCHIVE_FATAL);

			}

			/*

			 * Since there is no character-set regulation for

			 * symlink name, do not report the conversion error

			 * in an automatic conversion.

			 */

			if (sconv != zip->sconv_utf8 ||

			    (zip->entry->flags & ZIP_UTF8_NAME) == 0) {

				archive_set_error(&a->archive,

				    ARCHIVE_ERRNO_FILE_FORMAT,

				    "Symlink cannot be converted "

				    "from %s to current locale.",

				    archive_string_conversion_charset_name(

					sconv));

				ret = ARCHIVE_WARN;

			}

		}

	}

	if (rsrc) {

		int ret2 = zip_read_mac_metadata(a, entry, rsrc);

		if (ret2 < ret)

			ret = ret2;

	}

	return (ret);

}



static int

