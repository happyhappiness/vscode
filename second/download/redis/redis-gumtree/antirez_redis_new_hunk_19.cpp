 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "server.h"
#include <sys/stat.h>

#define ERROR(...) { \
    char __buf[1024]; \
