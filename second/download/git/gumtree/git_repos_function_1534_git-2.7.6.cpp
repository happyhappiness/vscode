static int color_empty(const struct color *c)
{
	return c->type <= COLOR_NORMAL;
}