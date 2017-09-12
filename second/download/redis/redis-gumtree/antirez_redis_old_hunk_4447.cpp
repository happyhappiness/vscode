 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <string.h>
#include "config.h"

static size_t used_memory = 0;

void *zmalloc(size_t size) {
    void *ptr = malloc(size+sizeof(size_t));

    if (!ptr) return NULL;
#ifdef HAVE_MALLOC_SIZE
    used_memory += redis_malloc_size(ptr);
    return ptr;
