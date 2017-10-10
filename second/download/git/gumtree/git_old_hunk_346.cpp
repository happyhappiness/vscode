static int sequencer_in_use;
static int use_editor = 1, include_status = 1;
static int show_ignored_in_status, have_option_m;
static const char *only_include_assumed;
static struct strbuf message = STRBUF_INIT;

static enum status_format {
	STATUS_FORMAT_NONE = 0,
	STATUS_FORMAT_LONG,
	STATUS_FORMAT_SHORT,
	STATUS_FORMAT_PORCELAIN,

	STATUS_FORMAT_UNSPECIFIED
} status_format = STATUS_FORMAT_UNSPECIFIED;

static int opt_parse_m(const struct option *opt, const char *arg, int unset)
{
	struct strbuf *buf = opt->value;
	if (unset) {
		have_option_m = 0;
