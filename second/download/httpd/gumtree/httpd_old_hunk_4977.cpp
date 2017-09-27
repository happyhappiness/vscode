 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mod_lua.h"
#include "util_script.h"
#include "lua_apr.h"
#include "lua_dbd.h"

APLOG_USE_MODULE(lua);

typedef char *(*req_field_string_f) (request_rec * r);
typedef int (*req_field_int_f) (request_rec * r);
typedef apr_table_t *(*req_field_apr_table_f) (request_rec * r);

void ap_lua_rstack_dump(lua_State *L, request_rec *r, const char *msg)
{
    int i;
    int top = lua_gettop(L);

    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(01484) "Lua Stack Dump: [%s]", msg);

    for (i = 1; i <= top; i++) {
        int t = lua_type(L, i);
        switch (t) {
        case LUA_TSTRING:{
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                              "%d:  '%s'", i, lua_tostring(L, i));
