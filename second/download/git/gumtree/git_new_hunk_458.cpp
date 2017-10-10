	GIT_COLOR_GREEN,	/* NEW */
	GIT_COLOR_YELLOW,	/* COMMIT */
	GIT_COLOR_BG_RED,	/* WHITESPACE */
	GIT_COLOR_NORMAL,	/* FUNCINFO */
};

static NORETURN void die_want_option(const char *option_name)
{
	die(_("option '%s' requires a value"), option_name);
}

static int parse_diff_color_slot(const char *var)
{
	if (!strcasecmp(var, "context") || !strcasecmp(var, "plain"))
		return DIFF_CONTEXT;
	if (!strcasecmp(var, "meta"))
		return DIFF_METAINFO;
