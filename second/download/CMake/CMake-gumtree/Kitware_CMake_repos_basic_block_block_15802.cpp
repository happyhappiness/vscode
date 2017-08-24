{
			struct tm tm;
			char buf[5];

			p = value;
			if (p == NULL || strlen(p) < 14)
				goto invalid_value;
			memset(&tm, 0, sizeof(tm));
			memcpy(buf, p, 4); buf[4] = '\0'; p += 4;
			tm.tm_year = strtol(buf, NULL, 10) - 1900;
			memcpy(buf, p, 2); buf[2] = '\0'; p += 2;
			tm.tm_mon = strtol(buf, NULL, 10) - 1;
			memcpy(buf, p, 2); buf[2] = '\0'; p += 2;
			tm.tm_mday = strtol(buf, NULL, 10);
			memcpy(buf, p, 2); buf[2] = '\0'; p += 2;
			tm.tm_hour = strtol(buf, NULL, 10);
			memcpy(buf, p, 2); buf[2] = '\0'; p += 2;
			tm.tm_min = strtol(buf, NULL, 10);
			memcpy(buf, p, 2); buf[2] = '\0';
			tm.tm_sec = strtol(buf, NULL, 10);
			iso9660->birth_time = mktime(&tm);
			return (ARCHIVE_OK);
		}