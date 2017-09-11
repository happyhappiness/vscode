 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sds.h"

#ifdef SDS_ABORT_ON_OOM
static void sdsOomAbort(void) {
    fprintf(stderr,"SDS: Out Of Memory (SDS_ABORT_ON_OOM defined)\n");
    abort();
}
#endif

sds sdsnewlen(const void *init, size_t initlen) {
    struct sdshdr *sh;
