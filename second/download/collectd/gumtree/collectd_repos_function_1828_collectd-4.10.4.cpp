static struct chain_head *
iptcc_find_label(const char *name, TC_HANDLE_T handle)
{
	struct list_head *pos;
	struct list_head *list_start_pos;
	unsigned int i=0;
	int res;

	if (list_empty(&handle->chains))
		return NULL;

	/* First look at builtin chains */
	list_for_each(pos, &handle->chains) {
		struct chain_head *c = list_entry(pos, struct chain_head, list);
		if (!iptcc_is_builtin(c))
			break;
		if (!strcmp(c->name, name))
			return c;
	}

	/* Find a smart place to start the search via chain index */
  	//list_start_pos = iptcc_linearly_search_chain_index(name, handle);
  	list_start_pos = iptcc_bsearch_chain_index(name, &i, handle);

	/* Handel if bsearch bails out early */
	if (list_start_pos == &handle->chains) {
		list_start_pos = pos;
	}
#ifdef DEBUG
	else {
		/* Verify result of bsearch against linearly index search */
		struct list_head *test_pos;
		struct chain_head *test_c, *tmp_c;
		test_pos = iptcc_linearly_search_chain_index(name, handle);
		if (list_start_pos != test_pos) {
			debug("BUG in chain_index search\n");
			test_c=list_entry(test_pos,      struct chain_head,list);
			tmp_c =list_entry(list_start_pos,struct chain_head,list);
			debug("Verify search found:\n");
			debug(" Chain:%s\n", test_c->name);
			debug("BSearch found:\n");
			debug(" Chain:%s\n", tmp_c->name);
			exit(42);
		}
	}
#endif

	/* Initial/special case, no user defined chains */
	if (handle->num_chains == 0)
		return NULL;

	/* Start searching through the chain list */
	list_for_each(pos, list_start_pos->prev) {
		struct chain_head *c = list_entry(pos, struct chain_head, list);
		res = strcmp(c->name, name);
		debug("List search name:%s == %s res:%d\n", name, c->name, res);
		if (res==0)
			return c;

		/* We can stop earlier as we know list is sorted */
		if (res>0 && !iptcc_is_builtin(c)) { /* Walked too far*/
			debug(" Not in list, walked too far, sorted list\n");
			return NULL;
		}

		/* Stop on wrap around, if list head is reached */
		if (pos == &handle->chains) {
			debug("Stop, list head reached\n");
			return NULL;
		}
	}

	debug("List search NOT found name:%s\n", name);
	return NULL;
}