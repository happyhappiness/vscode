void write_varint(int f, int32 x)
{
	char b[5];
	uchar bit;
	int cnt = 4;

	SIVAL(b, 1, x);

	while (cnt > 1 && b[cnt] == 0)
		cnt--;
	bit = ((uchar)1<<(7-cnt+1));
	if (CVAL(b, cnt) >= bit) {
		cnt++;
		*b = ~(bit-1);
	} else if (cnt > 1)
		*b = b[cnt] | ~(bit*2-1);
	else
		*b = b[cnt];

	write_buf(f, b, cnt);
}