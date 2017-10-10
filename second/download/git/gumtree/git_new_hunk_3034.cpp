		if (verbose)
			fprintf(stderr, "updating local tracking ref '%s'\n", rs.dst);
		if (ref->deletion) {
			delete_ref(rs.dst, NULL, 0);
		} else
			update_ref("update by push", rs.dst,
					ref->new_oid.hash, NULL, 0, 0);
		free(rs.dst);
	}
}

static void print_ref_status(char flag, const char *summary, struct ref *to, struct ref *from, const char *msg, int porcelain)
{
