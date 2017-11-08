char *getpass_r(const char *prompt, char *buffer, size_t buflen)
{
	long sts;
	short chan;
	struct _iosb iosb;
	$DESCRIPTOR(ttdesc, "TT");

	buffer[0]='\0';
	if ((sts = sys$assign(&ttdesc, &chan,0,0)) & 1) {
		if (((sts = sys$qiow(0, chan, IO$_READPROMPT | IO$M_NOECHO, &iosb, 0, 0, buffer, buflen, 0, 0, prompt, strlen(prompt))) & 1) && (iosb.iosb$w_status&1)) {
			buffer[iosb.iosb$w_bcnt] = '\0';
		} 
		sts = sys$dassgn(chan);
	}
	return buffer; /* we always return success */
}