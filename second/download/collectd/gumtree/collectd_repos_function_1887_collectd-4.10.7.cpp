int
TC_COMMIT(TC_HANDLE_T *handle)
{
	/* Replace, then map back the counters. */
	STRUCT_REPLACE *repl;
	STRUCT_COUNTERS_INFO *newcounters;
	struct chain_head *c;
	int ret;
	size_t counterlen;
	int new_number;
	unsigned int new_size;

	iptc_fn = TC_COMMIT;
	CHECK(*handle);

	/* Don't commit if nothing changed. */
	if (!(*handle)->changed)
		goto finished;

	new_number = iptcc_compile_table_prep(*handle, &new_size);
	if (new_number < 0) {
		errno = ENOMEM;
		goto out_zero;
	}

	repl = malloc(sizeof(*repl) + new_size);
	if (!repl) {
		errno = ENOMEM;
		goto out_zero;
	}
	memset(repl, 0, sizeof(*repl) + new_size);

#if 0
	TC_DUMP_ENTRIES(*handle);
#endif

	counterlen = sizeof(STRUCT_COUNTERS_INFO)
			+ sizeof(STRUCT_COUNTERS) * new_number;

	/* These are the old counters we will get from kernel */
	repl->counters = malloc(sizeof(STRUCT_COUNTERS)
				* (*handle)->info.num_entries);
	if (!repl->counters) {
		errno = ENOMEM;
		goto out_free_repl;
	}
	/* These are the counters we're going to put back, later. */
	newcounters = malloc(counterlen);
	if (!newcounters) {
		errno = ENOMEM;
		goto out_free_repl_counters;
	}
	memset(newcounters, 0, counterlen);

	strcpy(repl->name, (*handle)->info.name);
	repl->num_entries = new_number;
	repl->size = new_size;

	repl->num_counters = (*handle)->info.num_entries;
	repl->valid_hooks = (*handle)->info.valid_hooks;

	DEBUGP("num_entries=%u, size=%u, num_counters=%u\n",
		repl->num_entries, repl->size, repl->num_counters);

	ret = iptcc_compile_table(*handle, repl);
	if (ret < 0) {
		errno = ret;
		goto out_free_newcounters;
	}


#ifdef IPTC_DEBUG2
	{
		int fd = open("/tmp/libiptc-so_set_replace.blob", 
				O_CREAT|O_WRONLY);
		if (fd >= 0) {
			write(fd, repl, sizeof(*repl) + repl->size);
			close(fd);
		}
	}
#endif

	ret = setsockopt(sockfd, TC_IPPROTO, SO_SET_REPLACE, repl,
			 sizeof(*repl) + repl->size);
	if (ret < 0)
		goto out_free_newcounters;

	/* Put counters back. */
	strcpy(newcounters->name, (*handle)->info.name);
	newcounters->num_counters = new_number;

	list_for_each_entry(c, &(*handle)->chains, list) {
		struct rule_head *r;

		/* Builtin chains have their own counters */
		if (iptcc_is_builtin(c)) {
			DEBUGP("counter for chain-index %u: ", c->foot_index);
			switch(c->counter_map.maptype) {
			case COUNTER_MAP_NOMAP:
				counters_nomap(newcounters, c->foot_index);
				break;
			case COUNTER_MAP_NORMAL_MAP:
				counters_normal_map(newcounters, repl,
						    c->foot_index, 
						    c->counter_map.mappos);
				break;
			case COUNTER_MAP_ZEROED:
				counters_map_zeroed(newcounters, repl,
						    c->foot_index, 
						    c->counter_map.mappos,
						    &c->counters);
				break;
			case COUNTER_MAP_SET:
				counters_map_set(newcounters, c->foot_index,
						 &c->counters);
				break;
			}
		}

		list_for_each_entry(r, &c->rules, list) {
			DEBUGP("counter for index %u: ", r->index);
			switch (r->counter_map.maptype) {
			case COUNTER_MAP_NOMAP:
				counters_nomap(newcounters, r->index);
				break;

			case COUNTER_MAP_NORMAL_MAP:
				counters_normal_map(newcounters, repl,
						    r->index, 
						    r->counter_map.mappos);
				break;

			case COUNTER_MAP_ZEROED:
				counters_map_zeroed(newcounters, repl,
						    r->index,
						    r->counter_map.mappos,
						    &r->entry->counters);
				break;

			case COUNTER_MAP_SET:
				counters_map_set(newcounters, r->index,
						 &r->entry->counters);
				break;
			}
		}
	}

#ifdef IPTC_DEBUG2
	{
		int fd = open("/tmp/libiptc-so_set_add_counters.blob", 
				O_CREAT|O_WRONLY);
		if (fd >= 0) {
			write(fd, newcounters, counterlen);
			close(fd);
		}
	}
#endif

	ret = setsockopt(sockfd, TC_IPPROTO, SO_SET_ADD_COUNTERS,
			 newcounters, counterlen);
	if (ret < 0)
		goto out_free_newcounters;

	free(repl->counters);
	free(repl);
	free(newcounters);

finished:
	TC_FREE(handle);
	return 1;

out_free_newcounters:
	free(newcounters);
out_free_repl_counters:
	free(repl->counters);
out_free_repl:
	free(repl);
out_zero:
	return 0;
}