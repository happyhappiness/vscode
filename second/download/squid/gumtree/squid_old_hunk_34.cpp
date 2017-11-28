 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
 *
 */

#include "squid.h"
#include "structs.h"

#include "ConfigParser.h"
#include "acl/Gadgets.h"
#include "Store.h"
#include "Array.h"    // really Vector
#include "adaptation/Config.h"
#include "adaptation/Service.h"
#include "adaptation/AccessRule.h"
#include "adaptation/ServiceGroups.h"
#include "adaptation/History.h"


bool Adaptation::Config::Enabled = false;
char *Adaptation::Config::masterx_shared_name = NULL;
int Adaptation::Config::service_iteration_limit = 16;

void
Adaptation::Config::parseService()
{
    ServiceConfig *cfg = new ServiceConfig;
    if (!cfg->parse()) {
        fatalf("%s:%d: malformed adaptation service configuration",
               cfg_filename, config_lineno);
    }
    serviceConfigs.push_back(cfg);
}
