 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

static size_t used_memory = 0;

static void zmalloc_oom(size_t size) {
    fprintf(stderr, "zmalloc: Out of memory trying to allocate %lu bytes\n",
        size);
    fflush(stderr);
    abort();
}

void *zmalloc(size_t size) {
    void *ptr = malloc(size+sizeof(size_t));

    if (!ptr) zmalloc_oom(size);
#ifdef HAVE_MALLOC_SIZE
    used_memory += redis_malloc_size(ptr);
    return ptr;
