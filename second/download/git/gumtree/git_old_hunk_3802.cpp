#define SYMREF_MAXDEPTH 5

/* Include broken references in a do_for_each_ref*() iteration: */
#define DO_FOR_EACH_INCLUDE_BROKEN 0x01

/*
 * The common backend for the for_each_*ref* functions
 */
int do_for_each_ref(const char *submodule, const char *base,
		    each_ref_fn fn, int trim, int flags, void *cb_data);

int read_raw_ref(const char *refname, unsigned char *sha1,
		 struct strbuf *symref, unsigned int *flags);

#endif /* REFS_REFS_INTERNAL_H */
