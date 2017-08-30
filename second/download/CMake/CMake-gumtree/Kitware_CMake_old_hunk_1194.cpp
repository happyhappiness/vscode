			entries[i].flg |= MTIME_IS_SET;
			break;
		}
		p += 8;
		len -= 8;
	}

	free(timeBools);
	return (p - _p);
failed:
	free(timeBools);
	return (-1);
}

static ssize_t
decode_header_image(struct archive_read *a, struct _7zip *zip,
    struct _7z_stream_info *si, const unsigned char *p, uint64_t len,
    const void **image)
{
	const unsigned char *v;
	size_t vsize;
	int r;

	errno = 0;
	r = read_StreamsInfo(zip, si, p, len);
	if (r < 0) {
		if (errno == ENOMEM)
			archive_set_error(&a->archive, -1,
			    "Couldn't allocate memory");
