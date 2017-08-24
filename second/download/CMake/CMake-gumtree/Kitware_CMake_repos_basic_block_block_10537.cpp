{
				struct _7zip *zip =
				    (struct _7zip *)a->format->data;
				skip = p - (const char *)h;
				__archive_read_consume(a, skip);
				zip->seek_base = SFX_MIN_ADDR + offset + skip;
				return (ARCHIVE_OK);
			}