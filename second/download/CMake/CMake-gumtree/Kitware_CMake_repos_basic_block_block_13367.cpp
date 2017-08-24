(len+3 >= sizeof(buff)) {
			archive_strncat(as, (const char *)buff, len);
			len = 0;
			out = buff;
		}