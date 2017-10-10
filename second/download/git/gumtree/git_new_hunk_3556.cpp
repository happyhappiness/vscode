			fputc(')', stderr);
		}
		fputc('\n', stderr);
	}
}

static void print_ok_ref_status(struct ref *ref, int porcelain)
{
	if (ref->deletion)
		print_ref_status('-', "[deleted]", ref, NULL, NULL, porcelain);
	else if (is_null_oid(&ref->old_oid))
		print_ref_status('*',
