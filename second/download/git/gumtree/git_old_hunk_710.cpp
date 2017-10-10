
extern int finalize_object_file(const char *tmpfile, const char *filename);

extern int has_sha1_pack(const unsigned char *sha1);

/*
 * Return true iff we have an object named sha1, whether local or in
 * an alternate object database, and whether packed or loose.  This
 * function does not respect replace references.
 *
 * If the QUICK flag is set, do not re-check the pack directory
 * when we cannot find the object (this means we may give a false
