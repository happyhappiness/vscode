static int
dump_entry(struct ip6t_entry *e, const ip6tc_handle_t handle)
{
	size_t i;
	char buf[40];
	int len;
	struct ip6t_entry_target *t;
	
	printf("Entry %u (%lu):\n", iptcb_entry2index(handle, e),
	       iptcb_entry2offset(handle, e));
	puts("SRC IP: ");
	inet_ntop(AF_INET6, &e->ipv6.src, buf, sizeof buf);
	puts(buf);
	putchar('/');
	len = ipv6_prefix_length(&e->ipv6.smsk);
	if (len != -1)
		printf("%d", len);
	else {
		inet_ntop(AF_INET6, &e->ipv6.smsk, buf, sizeof buf);
		puts(buf);
	}
	putchar('\n');
	
	puts("DST IP: ");
	inet_ntop(AF_INET6, &e->ipv6.dst, buf, sizeof buf);
	puts(buf);
	putchar('/');
	len = ipv6_prefix_length(&e->ipv6.dmsk);
	if (len != -1)
		printf("%d", len);
	else {
		inet_ntop(AF_INET6, &e->ipv6.dmsk, buf, sizeof buf);
		puts(buf);
	}
	putchar('\n');
	
	printf("Interface: `%s'/", e->ipv6.iniface);
	for (i = 0; i < IFNAMSIZ; i++)
		printf("%c", e->ipv6.iniface_mask[i] ? 'X' : '.');
	printf("to `%s'/", e->ipv6.outiface);
	for (i = 0; i < IFNAMSIZ; i++)
		printf("%c", e->ipv6.outiface_mask[i] ? 'X' : '.');
	printf("\nProtocol: %u\n", e->ipv6.proto);
	if (e->ipv6.flags & IP6T_F_TOS)
		printf("TOS: %u\n", e->ipv6.tos);
	printf("Flags: %02X\n", e->ipv6.flags);
	printf("Invflags: %02X\n", e->ipv6.invflags);
	printf("Counters: %llu packets, %llu bytes\n",
	       (unsigned long long)e->counters.pcnt, (unsigned long long)e->counters.bcnt);
	printf("Cache: %08X\n", e->nfcache);
	
	IP6T_MATCH_ITERATE(e, print_match);

	t = ip6t_get_target(e);
	printf("Target name: `%s' [%u]\n", t->u.user.name, t->u.target_size);
	if (strcmp(t->u.user.name, IP6T_STANDARD_TARGET) == 0) {
		int pos = *(int *)t->data;
		if (pos < 0)
			printf("verdict=%s\n",
			       pos == -NF_ACCEPT-1 ? "NF_ACCEPT"
			       : pos == -NF_DROP-1 ? "NF_DROP"
			       : pos == IP6T_RETURN ? "RETURN"
			       : "UNKNOWN");
		else
			printf("verdict=%u\n", pos);
	} else if (strcmp(t->u.user.name, IP6T_ERROR_TARGET) == 0)
		printf("error=`%s'\n", t->data);

	printf("\n");
	return 0;
}