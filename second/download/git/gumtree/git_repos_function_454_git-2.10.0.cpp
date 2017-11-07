static align_type parse_align_position(const char *s)
{
	if (!strcmp(s, "right"))
		return ALIGN_RIGHT;
	else if (!strcmp(s, "middle"))
		return ALIGN_MIDDLE;
	else if (!strcmp(s, "left"))
		return ALIGN_LEFT;
	return -1;
}