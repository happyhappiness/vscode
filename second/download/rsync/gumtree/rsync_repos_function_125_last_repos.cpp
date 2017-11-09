const char *getallgroups(uid_t uid, item_list *gid_list)
{
	struct passwd *pw;
	gid_t *gid_array;
	int size;

	if ((pw = getpwuid(uid)) == NULL)
		return "getpwuid failed";

	gid_list->count = 0; /* We're overwriting any items in the list */
	EXPAND_ITEM_LIST(gid_list, gid_t, 32);
	size = gid_list->malloced;

	/* Get all the process's groups, with the pw_gid group first. */
	if (getgrouplist(pw->pw_name, pw->pw_gid, gid_list->items, &size) < 0) {
		if (size > (int)gid_list->malloced) {
			gid_list->count = gid_list->malloced;
			EXPAND_ITEM_LIST(gid_list, gid_t, size);
			if (getgrouplist(pw->pw_name, pw->pw_gid, gid_list->items, &size) < 0)
				size = -1;
		} else
			size = -1;
		if (size < 0)
			return "getgrouplist failed";
	}
	gid_list->count = size;
	gid_array = gid_list->items;

	/* Paranoia: is the default group not first in the list? */
	if (gid_array[0] != pw->pw_gid) {
		int j;
		for (j = 1; j < size; j++) {
			if (gid_array[j] == pw->pw_gid)
				break;
		}
		if (j == size) { /* The default group wasn't found! */
			EXPAND_ITEM_LIST(gid_list, gid_t, size+1);
			gid_array = gid_list->items;
		}
		gid_array[j] = gid_array[0];
		gid_array[0] = pw->pw_gid;
	}

	return NULL;
}