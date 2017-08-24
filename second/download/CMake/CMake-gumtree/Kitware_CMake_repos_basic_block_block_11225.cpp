(cbytes > 0) {
			(void)cab_read_ahead_cfdata(a, &avail);
			if (avail <= 0)
				return (ARCHIVE_FATAL);
			if (avail > cbytes)
				avail = (ssize_t)cbytes;
			if (cab_minimum_consume_cfdata(a, avail) < 0)
				return (ARCHIVE_FATAL);
			cbytes -= avail;
		}