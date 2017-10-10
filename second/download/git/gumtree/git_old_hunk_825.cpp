extern struct packed_git *find_sha1_pack(const unsigned char *sha1,
					 struct packed_git *packs);

extern void pack_report(void);

/*
 * mmap the index file for the specified packfile (if it is not
 * already mmapped).  Return 0 on success.
 */
extern int open_pack_index(struct packed_git *);

/*
