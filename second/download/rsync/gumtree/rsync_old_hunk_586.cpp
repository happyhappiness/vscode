   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

/* a lot of this stuff was originally derived from GNU tar, although
   it has now changed so much that it is hard to tell :) */

#include "rsync.h"

extern int verbose;
extern int delete_mode;

static struct exclude_struct **exclude_list;

/* build an exclude structure given a exclude pattern */
static struct exclude_struct *make_exclude(char *pattern, int include)
{
	struct exclude_struct *ret;

	ret = (struct exclude_struct *)malloc(sizeof(*ret));
	if (!ret) out_of_memory("make_exclude");

