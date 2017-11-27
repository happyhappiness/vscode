static void
do_check(TC_HANDLE_T h, unsigned int line)
{
	unsigned int i, n;
	unsigned int user_offset; /* Offset of first user chain */
	int was_return;

	assert(h->changed == 0 || h->changed == 1);
	if (strcmp(h->info.name, "filter") == 0) {
		assert(h->info.valid_hooks
		       == (1 << NF_IP6_LOCAL_IN
			   | 1 << NF_IP6_FORWARD
			   | 1 << NF_IP6_LOCAL_OUT));

		/* Hooks should be first three */
		assert(h->info.hook_entry[NF_IP6_LOCAL_IN] == 0);

		n = get_chain_end(h, 0);
		n += get_entry(h, n)->next_offset;
		assert(h->info.hook_entry[NF_IP6_FORWARD] == n);

		n = get_chain_end(h, n);
		n += get_entry(h, n)->next_offset;
		assert(h->info.hook_entry[NF_IP6_LOCAL_OUT] == n);

		user_offset = h->info.hook_entry[NF_IP6_LOCAL_OUT];
	} else if (strcmp(h->info.name, "nat") == 0) {
		assert((h->info.valid_hooks
			== (1 << NF_IP6_PRE_ROUTING
			    | 1 << NF_IP6_LOCAL_OUT
			    | 1 << NF_IP6_POST_ROUTING)) ||
		       (h->info.valid_hooks
			== (1 << NF_IP6_PRE_ROUTING
			    | 1 << NF_IP6_LOCAL_IN
			    | 1 << NF_IP6_LOCAL_OUT
			    | 1 << NF_IP6_POST_ROUTING)));

		assert(h->info.hook_entry[NF_IP6_PRE_ROUTING] == 0);

		n = get_chain_end(h, 0);

		n += get_entry(h, n)->next_offset;
		assert(h->info.hook_entry[NF_IP6_POST_ROUTING] == n);
		n = get_chain_end(h, n);

		n += get_entry(h, n)->next_offset;
		assert(h->info.hook_entry[NF_IP6_LOCAL_OUT] == n);
		user_offset = h->info.hook_entry[NF_IP6_LOCAL_OUT];

		if (h->info.valid_hooks & (1 << NF_IP6_LOCAL_IN)) {
			n = get_chain_end(h, n);
			n += get_entry(h, n)->next_offset;
			assert(h->info.hook_entry[NF_IP6_LOCAL_IN] == n);
			user_offset = h->info.hook_entry[NF_IP6_LOCAL_IN];
		}

	} else if (strcmp(h->info.name, "mangle") == 0) {
		/* This code is getting ugly because linux < 2.4.18-pre6 had
		 * two mangle hooks, linux >= 2.4.18-pre6 has five mangle hooks
		 * */
		assert((h->info.valid_hooks
			== (1 << NF_IP6_PRE_ROUTING
			    | 1 << NF_IP6_LOCAL_OUT)) ||
		       (h->info.valid_hooks
			== (1 << NF_IP6_PRE_ROUTING
			    | 1 << NF_IP6_LOCAL_IN
			    | 1 << NF_IP6_FORWARD
			    | 1 << NF_IP6_LOCAL_OUT
			    | 1 << NF_IP6_POST_ROUTING)));

		/* Hooks should be first five */
		assert(h->info.hook_entry[NF_IP6_PRE_ROUTING] == 0);

		n = get_chain_end(h, 0);

		if (h->info.valid_hooks & (1 << NF_IP6_LOCAL_IN)) {
			n += get_entry(h, n)->next_offset;
			assert(h->info.hook_entry[NF_IP6_LOCAL_IN] == n);
			n = get_chain_end(h, n);
		}

		if (h->info.valid_hooks & (1 << NF_IP6_FORWARD)) {
			n += get_entry(h, n)->next_offset;
			assert(h->info.hook_entry[NF_IP6_FORWARD] == n);
			n = get_chain_end(h, n);
		}

		n += get_entry(h, n)->next_offset;
		assert(h->info.hook_entry[NF_IP6_LOCAL_OUT] == n);
		user_offset = h->info.hook_entry[NF_IP6_LOCAL_OUT];

		if (h->info.valid_hooks & (1 << NF_IP6_POST_ROUTING)) {
			n = get_chain_end(h, n);
			n += get_entry(h, n)->next_offset;
			assert(h->info.hook_entry[NF_IP6_POST_ROUTING] == n);
			user_offset = h->info.hook_entry[NF_IP6_POST_ROUTING];
		}
	} else if (strcmp(h->info.name, "raw") == 0) {
		assert(h->info.valid_hooks
		       == (1 << NF_IP6_PRE_ROUTING
			   | 1 << NF_IP6_LOCAL_OUT));

		/* Hooks should be first three */
		assert(h->info.hook_entry[NF_IP6_PRE_ROUTING] == 0);

		n = get_chain_end(h, n);
		n += get_entry(h, n)->next_offset;
		assert(h->info.hook_entry[NF_IP6_LOCAL_OUT] == n);

		user_offset = h->info.hook_entry[NF_IP6_LOCAL_OUT];
	} else {
                fprintf(stderr, "Unknown table `%s'\n", h->info.name);
		abort();
	}

	/* User chain == end of last builtin + policy entry */
	user_offset = get_chain_end(h, user_offset);
	user_offset += get_entry(h, user_offset)->next_offset;

	/* Overflows should be end of entry chains, and unconditional
           policy nodes. */
	for (i = 0; i < NUMHOOKS; i++) {
		STRUCT_ENTRY *e;
		STRUCT_STANDARD_TARGET *t;

		if (!(h->info.valid_hooks & (1 << i)))
			continue;
		assert(h->info.underflow[i]
		       == get_chain_end(h, h->info.hook_entry[i]));

		e = get_entry(h, get_chain_end(h, h->info.hook_entry[i]));
		assert(unconditional(&e->ipv6));
		assert(e->target_offset == sizeof(*e));
		t = (STRUCT_STANDARD_TARGET *)GET_TARGET(e);
		printf("target_size=%u, align=%u\n",
			t->target.u.target_size, ALIGN(sizeof(*t)));
		assert(t->target.u.target_size == ALIGN(sizeof(*t)));
		assert(e->next_offset == sizeof(*e) + ALIGN(sizeof(*t)));

		assert(strcmp(t->target.u.user.name, STANDARD_TARGET)==0);
		assert(t->verdict == -NF_DROP-1 || t->verdict == -NF_ACCEPT-1);

		/* Hooks and underflows must be valid entries */
		iptcb_entry2index(h, get_entry(h, h->info.hook_entry[i]));
		iptcb_entry2index(h, get_entry(h, h->info.underflow[i]));
	}

	assert(h->info.size
	       >= h->info.num_entries * (sizeof(STRUCT_ENTRY)
					 +sizeof(STRUCT_STANDARD_TARGET)));

	assert(h->entries.size
	       >= (h->new_number
		   * (sizeof(STRUCT_ENTRY)
		      + sizeof(STRUCT_STANDARD_TARGET))));
	assert(strcmp(h->info.name, h->entries.name) == 0);

	i = 0; n = 0;
	was_return = 0;

#if 0
	/* Check all the entries. */
	ENTRY_ITERATE(h->entries.entrytable, h->entries.size,
		      check_entry, &i, &n, user_offset, &was_return, h);

	assert(i == h->new_number);
	assert(n == h->entries.size);

	/* Final entry must be error node */
	assert(strcmp(GET_TARGET(index2entry(h, h->new_number-1))
		      ->u.user.name,
		      ERROR_TARGET) == 0);
#endif
}