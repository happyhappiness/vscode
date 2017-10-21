
static struct idlist *uidlist;
static struct idlist *gidlist;

static struct idlist *add_list(int id, char *name)
{
	struct idlist *list = (struct idlist *)malloc(sizeof(list[0]));
	if (!list) out_of_memory("add_list");
	list->next = NULL;
	list->name = strdup(name);
	if (!list->name) out_of_memory("add_list");
	list->id = (int)id;
	return list;
