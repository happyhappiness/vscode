 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
 *
 */
#include "config.h"
#include "Debug.h"
#include "SquidTime.h"
#include "util.h"

/* for shutting_down flag in xassert() */
#include "globals.h"

/* cope with no squid.h */
#ifndef MAXPATHLEN
#define MAXPATHLEN 256
#endif

char *Debug::debugOptions = NULL;
int Debug::override_X = 0;
int Debug::log_stderr = -1;
bool Debug::log_syslog = false;
int Debug::Levels[MAX_DEBUG_SECTIONS];
int Debug::level;
char *Debug::cache_log = NULL;
int Debug::rotateNumber = -1;
FILE *debug_log = NULL;
static char *debug_log_file = NULL;
static int Ctx_Lock = 0;
static const char *debugLogTime(void);
static void ctx_print(void);
#if HAVE_SYSLOG
#ifdef LOG_LOCAL4
static int syslog_facility = 0;
#endif
static void _db_print_syslog(const char *format, va_list args);
#endif
static void _db_print_stderr(const char *format, va_list args);
static void _db_print_file(const char *format, va_list args);

#ifdef _SQUID_MSWIN_
SQUIDCEXTERN LPCRITICAL_SECTION dbg_mutex;
typedef BOOL (WINAPI * PFInitializeCriticalSectionAndSpinCount) (LPCRITICAL_SECTION, DWORD);
#endif

void
_db_print(const char *format,...)
