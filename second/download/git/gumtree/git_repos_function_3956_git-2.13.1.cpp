static struct dir_entry *find_dir_entry(struct index_state *istate,
		const char *name, unsigned int namelen)
{
	return find_dir_entry__hash(istate, name, namelen, memihash(name, namelen));
}