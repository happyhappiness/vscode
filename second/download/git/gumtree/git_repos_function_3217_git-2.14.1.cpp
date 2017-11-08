static void debug_name_entry(int i, struct name_entry *n)
{
	printf("ent#%d %06o %s\n", i,
	       n->path ? n->mode : 0,
	       n->path ? n->path : "(missing)");
}