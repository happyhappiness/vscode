 * KIND, either express or implied.
 *
 ***************************************************************************/

#include <stdarg.h>
#include <stdio.h> /* needed for FILE */
#include "curl.h"  /* for CURL_EXTERN */

#ifdef  __cplusplus
extern "C" {
#endif

CURL_EXTERN int curl_mprintf(const char *format, ...);
