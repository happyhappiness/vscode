
int color_parse(const char *value, char *dst)
{
	return color_parse_mem(value, strlen(value), dst);
}

/*
 * Write the ANSI color codes for "c" to "out"; the string should
 * already have the ANSI escape code in it. "out" should have enough
 * space in it to fit any color.
 */
static char *color_output(char *out, const struct color *c, char type)
{
	switch (c->type) {
	case COLOR_UNSPECIFIED:
	case COLOR_NORMAL:
		break;
	case COLOR_ANSI:
		*out++ = type;
		*out++ = '0' + c->value;
		break;
	case COLOR_256:
		out += sprintf(out, "%c8;5;%d", type, c->value);
		break;
	case COLOR_RGB:
		out += sprintf(out, "%c8;2;%d;%d;%d", type,
			       c->red, c->green, c->blue);
		break;
	}
	return out;
}

static int color_empty(const struct color *c)
