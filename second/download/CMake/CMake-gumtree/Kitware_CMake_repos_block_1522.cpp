{
		/* generate one, grrrr */
		warc_uuid_t u;

		_gen_uuid(&u);
		/* Unfortunately, archive_string_sprintf does not
		 * handle the minimum number following '%'.
		 * So we have to use snprintf function here instead
		 * of archive_string_snprintf function. */
#if defined(_WIN32) && !defined(__CYGWIN__) && !( defined(_MSC_VER) && _MSC_VER >= 1900)
#define snprintf _snprintf
#endif
		snprintf(
			std_uuid, sizeof(std_uuid),
			"<urn:uuid:%08x-%04x-%04x-%04x-%04x%08x>",
			u.u[0U],
			u.u[1U] >> 16U, u.u[1U] & 0xffffU,
			u.u[2U] >> 16U, u.u[2U] & 0xffffU,
			u.u[3U]);
		hdr.recid = std_uuid;
	}