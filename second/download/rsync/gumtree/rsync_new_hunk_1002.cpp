
/* If the source username/group does not exist on the target then use
 * the numeric IDs.  Never do any mapping for uid=0 or gid=0 as these
 * are special. */

#include "rsync.h"
#include "ifuncs.h"
#include "itypes.h"
#include "io.h"

extern int am_root;
extern int preserve_uid;
extern int preserve_gid;
extern int preserve_acls;
extern int numeric_ids;
extern gid_t our_gid;
extern char *usermap;
extern char *groupmap;

#ifdef HAVE_GETGROUPS
# ifndef GETGROUPS_T
#  define GETGROUPS_T gid_t
# endif
#endif

#define NFLAGS_WILD_NAME_MATCH (1<<0)
#define NFLAGS_NAME_MATCH (1<<1)

union name_or_id {
    const char *name;
    id_t max_id;
};

struct idlist {
	struct idlist *next;
	union name_or_id u;
	id_t id, id2;
	uint16 flags;
};

static struct idlist *uidlist, *uidmap;
static struct idlist *gidlist, *gidmap;

static id_t id_parse(const char *num_str)
{
	id_t tmp, num = 0;
	const char *cp = num_str;

	while (*cp) {
		if (!isDigit(cp)) {
		  invalid_num:
			rprintf(FERROR, "Invalid ID number: %s\n", num_str);
			exit_cleanup(RERR_SYNTAX);
		}
		tmp = num * 10 + *cp++ - '0';
		if (tmp < num)
			goto invalid_num;
		num = tmp;
	}

	return num;
}

static struct idlist *add_to_list(struct idlist **root, id_t id, union name_or_id noiu,
				  id_t id2, uint16 flags)
{
	struct idlist *node = new(struct idlist);
	if (!node)
		out_of_memory("add_to_list");
	node->next = *root;
	node->u = noiu;
	node->id = id;
	node->id2 = id2;
	node->flags = flags;
	*root = node;
	return node;
}

/* turn a uid into a user name */
char *uid_to_user(uid_t uid)
{
	struct passwd *pass = getpwuid(uid);
	if (pass)
		return strdup(pass->pw_name);
	return NULL;
}

/* turn a gid into a group name */
char *gid_to_group(gid_t gid)
{
	struct group *grp = getgrgid(gid);
	if (grp)
		return strdup(grp->gr_name);
	return NULL;
}

/* Parse a user name or (optionally) a number into a uid */
int user_to_uid(const char *name, uid_t *uid_p, BOOL num_ok)
{
	struct passwd *pass;
	if (!name || !*name)
		return 0;
	if (num_ok && name[strspn(name, "0123456789")] == '\0') {
		*uid_p = id_parse(name);
		return 1;
	}
	if (!(pass = getpwnam(name)))
		return 0;
	*uid_p = pass->pw_uid;
	return 1;
}

/* Parse a group name or (optionally) a number into a gid */
int group_to_gid(const char *name, gid_t *gid_p, BOOL num_ok)
{
	struct group *grp;
	if (!name || !*name)
		return 0;
	if (num_ok && name[strspn(name, "0123456789")] == '\0') {
		*gid_p = id_parse(name);
		return 1;
	}
	if (!(grp = getgrnam(name)))
		return 0;
	*gid_p = grp->gr_gid;
	return 1;
}

static int is_in_group(gid_t gid)
{
#ifdef HAVE_GETGROUPS
	static gid_t last_in;
