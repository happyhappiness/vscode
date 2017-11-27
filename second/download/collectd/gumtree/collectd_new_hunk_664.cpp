 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *   Florian octo Forster <octo at collectd.org>
 *   Sebastian tokkee Harl <sh at tokkee.org>
 **/

#include "collectd.h"

#include "common.h"
#include "utils_cmd_putval.h"

/*
 * private helper functions
 */

static int set_option(value_list_t *vl, const char *key, const char *value) {
  if ((vl == NULL) || (key == NULL) || (value == NULL))
    return (-1);

  if (strcasecmp("interval", key) == 0) {
