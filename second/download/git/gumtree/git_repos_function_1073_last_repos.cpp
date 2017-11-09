static const char *color(int slot, struct wt_status *s)
{
	const char *c = "";
	if (want_color(s->use_color))
		c = s->color_palette[slot];
	if (slot == WT_STATUS_ONBRANCH && color_is_nil(c))
		c = s->color_palette[WT_STATUS_HEADER];
	return c;
}