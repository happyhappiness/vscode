static int flush_delete_delay(void)
{
	if (deldelay_fd < 0 && !start_delete_delay_temp())
		return 0;
	if (write(deldelay_fd, deldelay_buf, deldelay_cnt) != deldelay_cnt) {
		rsyserr(FERROR, errno, "flush of delete-delay buffer");
		delete_during = 0;
		delete_after = !inc_recurse;
		close(deldelay_fd);
		return 0;
	}
	deldelay_cnt = 0;
	return 1;
}