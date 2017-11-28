 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
 *
 */

#include "config.h"
#include "squid.h"

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>

#include "DiskIO/DiskDaemon/diomsg.h"

void
xassert(const char *msg, const char *file, int line)
{
    fprintf(stderr,"assertion failed: %s:%d: \"%s\"\n", file, line, msg);

