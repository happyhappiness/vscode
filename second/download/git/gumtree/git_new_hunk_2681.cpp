			die_errno(_("could not close %s"), path);
		return -1;
	}
	return 0;
}

int write_file(const char *path, const char *fmt, ...)
{
	int status;
	va_list params;

	va_start(params, fmt);
	status = write_file_v(path, 1, fmt, params);
	va_end(params);
	return status;
}

int write_file_gently(const char *path, const char *fmt, ...)
{
	int status;
	va_list params;

	va_start(params, fmt);
	status = write_file_v(path, 0, fmt, params);
	va_end(params);
	return status;
}

void sleep_millisec(int millisec)
{
	poll(NULL, 0, millisec);
}
