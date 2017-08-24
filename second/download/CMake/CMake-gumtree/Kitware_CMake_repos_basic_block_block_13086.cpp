{
		const void *d;
		size_t outbytes, used;

		r = move_reading_point(a, xattr->offset);
		if (r != ARCHIVE_OK)
			break;
		r = rd_contents_init(a, xattr->encoding,
		    xattr->a_sum.alg, xattr->e_sum.alg);
		if (r != ARCHIVE_OK)
			break;
		d = NULL;
		r = rd_contents(a, &d, &outbytes, &used, xattr->length);
		if (r != ARCHIVE_OK)
			break;
		if (outbytes != xattr->size) {
			archive_set_error(&(a->archive), ARCHIVE_ERRNO_MISC,
			    "Decompressed size error");
			r = ARCHIVE_FATAL;
			break;
		}
		r = checksum_final(a,
		    xattr->a_sum.val, xattr->a_sum.len,
		    xattr->e_sum.val, xattr->e_sum.len);
		if (r != ARCHIVE_OK)
			break;
		archive_entry_xattr_add_entry(entry,
		    xattr->name.s, d, outbytes);
		xattr = xattr->next;
	}