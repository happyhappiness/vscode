static int mailmap_name(const char **email, size_t *email_len,
			const char **name, size_t *name_len)
{
	static struct string_list *mail_map;
	if (!mail_map) {
		mail_map = xcalloc(1, sizeof(*mail_map));
		read_mailmap(mail_map, NULL);
	}
	return mail_map->nr && map_user(mail_map, email, email_len, name, name_len);
}