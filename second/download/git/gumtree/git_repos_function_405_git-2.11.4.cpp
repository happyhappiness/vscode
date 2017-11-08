static inline int cmit_fmt_is_mail(enum cmit_fmt fmt)
{
	return (fmt == CMIT_FMT_EMAIL || fmt == CMIT_FMT_MBOXRD);
}