
/* If the source username/group does not exist on the target then use
 * the numeric IDs.  Never do any mapping for uid=0 or gid=0 as these
 * are special. */

#include "rsync.h"
#include "io.h"

extern int verbose;
extern int am_root;
extern int preserve_uid;
extern int preserve_gid;
extern int preserve_acls;
extern int numeric_ids;

#ifdef HAVE_GETGROUPS
# ifndef GETGROUPS_T
#  define GETGROUPS_T gid_t
# endif
#endif

struct idlist {
	struct idlist *next;
	const char *name;
	id_t id, id2;
	uint16 flags;
};

static struct idlist *uidlist;
static struct idlist *gidlist;

static struct idlist *add_to_list(struct idlist **root, id_t id, const char *name,
				  id_t id2, uint16 flags)
{
	struct idlist *node = new(struct idlist);
	if (!node)
		out_of_memory("add_to_list");
	node->next = *root;
	node->name = name;
	node->id = id;
	node->id2 = id2;
	node->flags = flags;
	*root = node;
	return node;
}

/* turn a uid into a user name */
static const char *uid_to_name(uid_t uid)
{
	struct passwd *pass = getpwuid(uid);
	if (pass)
		return strdup(pass->pw_name);
	return NULL;
}

/* turn a gid into a group name */
static const char *gid_to_name(gid_t gid)
{
	struct group *grp = getgrgid(gid);
	if (grp)
		return strdup(grp->gr_name);
	return NULL;
}

static uid_t map_uid(uid_t id, const char *name)
{
	uid_t uid;
	if (id != 0 && name_to_uid(name, &uid))
		return uid;
	return id;
}

static gid_t map_gid(gid_t id, const char *name)
{
	gid_t gid;
	if (id != 0 && name_to_gid(name, &gid))
		return gid;
	return id;
}

static int is_in_group(gid_t gid)
{
#ifdef HAVE_GETGROUPS
	static gid_t last_in;
