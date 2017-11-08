void free_pack_by_name(const char *pack_name)
{
	struct packed_git *p, **pp = &packed_git;

	while (*pp) {
		p = *pp;
		if (strcmp(pack_name, p->pack_name) == 0) {
			clear_delta_base_cache();
			close_pack_windows(p);
			if (p->pack_fd != -1) {
				close(p->pack_fd);
				pack_open_fds--;
			}
			close_pack_index(p);
			free(p->bad_object_sha1);
			*pp = p->next;
			if (last_found_pack == p)
				last_found_pack = NULL;
			free(p);
			return;
		}
		pp = &p->next;
	}
}