  * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  * POSSIBILITY OF SUCH DAMAGE.
  */
 
-#include "fmacros.h"
-#include <stdlib.h>
-#include <stdio.h>
-#include <string.h>
-#include <unistd.h>
+#include "server.h"
 #include <sys/stat.h>
-#include "config.h"
 
 #define ERROR(...) { \
     char __buf[1024]; \
     sprintf(__buf, __VA_ARGS__); \
     sprintf(error, "0x%16llx: %s", (long long)epos, __buf); \
 }
