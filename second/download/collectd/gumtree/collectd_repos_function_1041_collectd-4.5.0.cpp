int
dump_entry(STRUCT_ENTRY *e, const TC_HANDLE_T handle)
{
	size_t i;
	STRUCT_ENTRY_TARGET *t;

	printf("Entry %u (%lu):\n", iptcb_entry2index(handle, e),
	       iptcb_entry2offset(handle, e));
	printf("SRC IP: %u.%u.%u.%u/%u.%u.%u.%u\n",
	       IP_PARTS(e->ip.src.s_addr),IP_PARTS(e->ip.smsk.s_addr));
	printf("DST IP: %u.%u.%u.%u/%u.%u.%u.%u\n",
	       IP_PARTS(e->ip.dst.s_addr),IP_PARTS(e->ip.dmsk.s_addr));
	printf("Interface: `%s'/", e->ip.iniface);
	for (i = 0; i < IFNAMSIZ; i++)
		printf("%c", e->ip.iniface_mask[i] ? 'X' : '.');
	printf("to `%s'/", e->ip.outiface);
	for (i = 0; i < IFNAMSIZ; i++)
		printf("%c", e->ip.outiface_mask[i] ? 'X' : '.');
	printf("\nProtocol: %u\n", e->ip.proto);
	printf("Flags: %02X\n", e->ip.flags);
	printf("Invflags: %02X\n", e->ip.invflags);
	printf("Counters: %llu packets, %llu bytes\n",
	       (unsigned long long)e->counters.pcnt, (unsigned long long)e->counters.bcnt);
	printf("Cache: %08X\n", e->nfcache);

	IPT_MATCH_ITERATE(e, print_match);

	t = GET_TARGET(e);
	printf("Target name: `%s' [%u]\n", t->u.user.name, t->u.target_size);
	if (strcmp(t->u.user.name, STANDARD_TARGET) == 0) {
		int pos = *(int *)t->data;
		if (pos < 0)
			printf("verdict=%s\n",
			       pos == -NF_ACCEPT-1 ? "NF_ACCEPT"
			       : pos == -NF_DROP-1 ? "NF_DROP"
			       : pos == -NF_QUEUE-1 ? "NF_QUEUE"
			       : pos == RETURN ? "RETURN"
			       : "UNKNOWN");
		else
			printf("verdict=%u\n", pos);
	} else if (strcmp(t->u.user.name, IPT_ERROR_TARGET) == 0)
		printf("error=`%s'\n", t->data);

	printf("\n");
	return 0;
}