static void duplicate_conf(struct conf_info *dst, const struct conf_info *src)
{
	*dst = *src;
	dst->name = xstrdup_or_null(src->name);
	dst->key = xstrdup_or_null(src->key);
	dst->command = xstrdup_or_null(src->command);
}