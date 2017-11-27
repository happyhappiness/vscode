 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <assert.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/socket.h>
#include <netdb.h>

#include <netinet/in_systm.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#ifdef HAVE_NETINET_IP_VAR_H
# include <netinet/ip_var.h>
#endif

#include <netinet/ip6.h>
#include <netinet/icmp6.h>

#include <sys/time.h>
#include <time.h>

#include "liboping.h"

#if DEBUG
# define dprintf(...) printf ("%s[%4i]: %-20s: ", __FILE__, __LINE__, __FUNCTION__); printf (__VA_ARGS__)
#else
