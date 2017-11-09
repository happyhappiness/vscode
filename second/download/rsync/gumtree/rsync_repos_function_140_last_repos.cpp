void send_msg_int(enum msgcode code, int num)
{
	char numbuf[4];

	if (DEBUG_GTE(IO, 1))
		rprintf(FINFO, "[%s] send_msg_int(%d, %d)\n", who_am_i(), (int)code, num);

	SIVAL(numbuf, 0, num);
	send_msg(code, numbuf, 4, -1);
}