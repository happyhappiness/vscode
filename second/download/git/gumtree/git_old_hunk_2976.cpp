		if (!wildmatch(p, refname, WM_PATHNAME, NULL))
			return 1;
	}
	return 0;
}

/* Allocate space for a new ref_array_item and copy the objectname and flag to it */
static struct ref_array_item *new_ref_array_item(const char *refname,
						 const unsigned char *objectname,
						 int flag)
{
	size_t len = strlen(refname);
