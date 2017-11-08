void send_msg_int(enum msgcode code, int num)
{
	char numbuf[4];
	SIVAL(numbuf, 0, num);
	send_msg(code, numbuf, 4, 0);
}