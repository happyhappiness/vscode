static int remember_delete(struct file_struct *file, const char *fname, int flags)
{
	int len;

	if (deldelay_cnt == deldelay_size && !flush_delete_delay())
		return 0;

	if (flags & DEL_NO_UID_WRITE)
		deldelay_buf[deldelay_cnt++] = '!';

	while (1) {
		len = snprintf(deldelay_buf + deldelay_cnt,
			       deldelay_size - deldelay_cnt,
			       "%x %s%c",
			       (int)file->mode, fname, '\0');
		if ((deldelay_cnt += len) <= deldelay_size)
			break;
		deldelay_cnt -= len;
		if (!flush_delete_delay())
			return 0;
	}

	return 1;
}