static struct cmd2process *find_multi_file_filter_entry(struct hashmap *hashmap, const char *cmd)
{
	struct cmd2process key;
	hashmap_entry_init(&key, strhash(cmd));
	key.cmd = cmd;
	return hashmap_get(hashmap, &key, NULL);
}