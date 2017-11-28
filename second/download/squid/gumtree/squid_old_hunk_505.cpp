 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
 *
 */
#include "squid.h"
#include "acl/Acl.h"
#include "acl/Checklist.h"
#include "anyp/PortCfg.h"
#include "ConfigParser.h"
#include "Debug.h"
#include "dlink.h"
#include "globals.h"
#include "SquidConfig.h"

const char *AclMatchedName = NULL;

void *
ACL::operator new (size_t byteCount)
{
    fatal ("unusable ACL::new");
    return (void *)1;
}
