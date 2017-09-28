 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "redis.h"

/* -----------------------------------------------------------------------------
 * Helpers and low level bit functions.
 * -------------------------------------------------------------------------- */

/* This helper function used by GETBIT / SETBIT parses the bit offset argument
 * making sure an error is returned if it is negative or if it overflows
 * Redis 512 MB limit for the string value. */
static int getBitOffsetFromArgument(redisClient *c, robj *o, size_t *offset) {
    long long loffset;
    char *err = "bit offset is not an integer or out of range";

    if (getLongLongFromObjectOrReply(c,o,&loffset,err) != REDIS_OK)
        return REDIS_ERR;

    /* Limit offset to 512MB in bytes */
    if ((loffset < 0) || ((unsigned long long)loffset >> 3) >= (512*1024*1024))
    {
        addReplyError(c,err);
        return REDIS_ERR;
    }

    *offset = (size_t)loffset;
    return REDIS_OK;
}

/* Count number of bits set in the binary array pointed by 's' and long
 * 'count' bytes. The implementation of this function is required to
 * work with a input string length up to 512 MB. */
size_t redisPopcount(void *s, long count) {
    size_t bits = 0;
    unsigned char *p = s;
