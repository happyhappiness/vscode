struct subprocess_entry *subprocess_find_entry(struct hashmap *hashmap, const char *cmd)
{
	struct subprocess_entry key;

	hashmap_entry_init(&key, strhash(cmd));
	key.cmd = cmd;
	return hashmap_get(hashmap, &key, NULL);
}