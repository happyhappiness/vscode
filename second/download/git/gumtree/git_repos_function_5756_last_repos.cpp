static void format_display(struct strbuf *display, char code,
			   const char *summary, const char *error,
			   const char *remote, const char *local,
			   int summary_width)
{
	int width = (summary_width + strlen(summary) - gettext_width(summary));

	strbuf_addf(display, "%c %-*s ", code, width, summary);
	if (!compact_format)
		print_remote_to_local(display, remote, local);
	else
		print_compact(display, remote, local);
	if (error)
		strbuf_addf(display, "  (%s)", error);
}