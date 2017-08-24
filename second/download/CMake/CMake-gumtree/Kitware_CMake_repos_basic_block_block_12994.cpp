{
	case WT_RSRC:
	case WT_RSP:
		/* only try and read the filename in the cases that are
		 * guaranteed to have one */
		fnam = _warc_rduri(buf, eoh - buf);
		/* check the last character in the URI to avoid creating
		 * directory endpoints as files, see Todo above */
		if (fnam.len == 0 || fnam.str[fnam.len - 1] == '/') {
			/* break here for now */
			fnam.len = 0U;
			fnam.str = NULL;
			break;
		}
		/* bang to our string pool, so we save a
		 * malloc()+free() roundtrip */
		if (fnam.len + 1U > w->pool.len) {
			w->pool.len = ((fnam.len + 64U) / 64U) * 64U;
			w->pool.str = realloc(w->pool.str, w->pool.len);
		}
		memcpy(w->pool.str, fnam.str, fnam.len);
		w->pool.str[fnam.len] = '\0';
		/* let no one else know about the pool, it's a secret, shhh */
		fnam.str = w->pool.str;

		/* snarf mtime or deduce from rtime
		 * this is a custom header added by our writer, it's quite
		 * hard to believe anyone else would go through with it
		 * (apart from being part of some http responses of course) */
		if ((mtime = _warc_rdmtm(buf, eoh - buf)) == (time_t)-1) {
			mtime = rtime;
		}
		break;
	default:
		fnam.len = 0U;
		fnam.str = NULL;
		break;
	}