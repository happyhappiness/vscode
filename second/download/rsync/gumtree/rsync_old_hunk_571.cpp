extern int sanitize_paths;

static char topsrcname[MAXPATHLEN];

static struct exclude_struct **local_exclude_list;

static void clean_flist(struct file_list *flist, int strip_root);


static void list_file_entry(struct file_struct *f)
{
	char perms[11] = "----------";
	char *perm_map = "rwxrwxrwx";
	int i;
