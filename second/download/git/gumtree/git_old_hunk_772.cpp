
#define ERRORMSG(o,type) \
	( ((o) && (o)->msgs[(type)]) \
	  ? ((o)->msgs[(type)])      \
	  : (unpack_plumbing_errors[(type)]) )

void setup_unpack_trees_porcelain(struct unpack_trees_options *opts,
				  const char *cmd)
{
	int i;
	const char **msgs = opts->msgs;
	const char *msg;
