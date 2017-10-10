			add_object_entry(o->oid.hash, o->type, "", 0);
		}
	}
	free(in_pack.array);
}

static int has_sha1_pack_kept_or_nonlocal(const unsigned char *sha1)
{
	static struct packed_git *last_found = (void *)1;
	struct packed_git *p;

	p = (last_found != (void *)1) ? last_found : packed_git;
