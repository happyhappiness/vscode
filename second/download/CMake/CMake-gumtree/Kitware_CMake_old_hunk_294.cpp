			add_pax_attr(&(pax->pax_header), "SCHILY.fflags", p);



		/* I use star-compatible ACL attributes. */

		r = archive_entry_acl_text_l(entry_original,

		    ARCHIVE_ENTRY_ACL_TYPE_ACCESS |

		    ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID,

		    &p, NULL, pax->sconv_utf8);

		if (r != 0) {

			if (errno == ENOMEM) {

				archive_set_error(&a->archive, ENOMEM,

				    "Can't allocate memory for "

				    "ACL.access");

				return (ARCHIVE_FATAL);

			}

			archive_set_error(&a->archive,

			    ARCHIVE_ERRNO_FILE_FORMAT,

			    "Can't translate ACL.access to UTF-8");

			ret = ARCHIVE_WARN;

		} else if (p != NULL && *p != '\0') {

			add_pax_attr(&(pax->pax_header),

			    "SCHILY.acl.access", p);

		}

		r = archive_entry_acl_text_l(entry_original,

		    ARCHIVE_ENTRY_ACL_TYPE_DEFAULT |

		    ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID,

		    &p, NULL, pax->sconv_utf8);

		if (r != 0) {

			if (errno == ENOMEM) {

				archive_set_error(&a->archive, ENOMEM,

				    "Can't allocate memory for "

				    "ACL.default");

				return (ARCHIVE_FATAL);

			}

			archive_set_error(&a->archive,

			    ARCHIVE_ERRNO_FILE_FORMAT,

			    "Can't translate ACL.default to UTF-8");

			ret = ARCHIVE_WARN;

		} else if (p != NULL && *p != '\0') {

			add_pax_attr(&(pax->pax_header),

			    "SCHILY.acl.default", p);

		}



		/* We use GNU-tar-compatible sparse attributes. */
