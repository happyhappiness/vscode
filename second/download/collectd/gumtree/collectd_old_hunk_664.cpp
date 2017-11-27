 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *   Florian octo Forster <octo at collectd.org>
 **/

#include "collectd.h"

#include "common.h"
#include "plugin.h"

#include "utils_cmd_putval.h"
#include "utils_parse_option.h"

#define print_to_socket(fh, ...)                                               \
  do {                                                                         \
    if (fprintf(fh, __VA_ARGS__) < 0) {                                        \
      char errbuf[1024];                                                       \
      WARNING("handle_putval: failed to write to socket #%i: %s", fileno(fh),  \
              sstrerror(errno, errbuf, sizeof(errbuf)));                       \
      sfree(vl.values);                                                        \
      return -1;                                                               \
    }                                                                          \
    fflush(fh);                                                                \
  } while (0)

static int set_option(value_list_t *vl, const char *key, const char *value) {
  if ((vl == NULL) || (key == NULL) || (value == NULL))
    return (-1);

  if (strcasecmp("interval", key) == 0) {
