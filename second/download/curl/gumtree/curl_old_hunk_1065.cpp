 * KIND, either express or implied.
 *
 ***************************************************************************/

#include <stdarg.h>
#include <stdio.h> /* needed for FILE */

#include "curl.h"

#ifdef  __cplusplus
extern "C" {
#endif

CURL_EXTERN int curl_mprintf(const char *format, ...);
