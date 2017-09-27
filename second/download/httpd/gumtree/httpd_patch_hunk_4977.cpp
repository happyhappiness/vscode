  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  */
 
 #include "mod_lua.h"
-#include "util_script.h"
 #include "lua_apr.h"
 #include "lua_dbd.h"
+#include "lua_passwd.h"
+#include "scoreboard.h"
+#include "util_md5.h"
+#include "util_script.h"
+#include "util_varbuf.h"
+#include "apr_date.h"
+#include "apr_pools.h"
+#include "apr_thread_mutex.h"
+
+#include <lua.h>
+
+extern apr_thread_mutex_t* lua_ivm_mutex;
 
 APLOG_USE_MODULE(lua);
+#define POST_MAX_VARS 500
+
+#ifndef MODLUA_MAX_REG_MATCH
+#define MODLUA_MAX_REG_MATCH 25
+#endif
 
 typedef char *(*req_field_string_f) (request_rec * r);
 typedef int (*req_field_int_f) (request_rec * r);
 typedef apr_table_t *(*req_field_apr_table_f) (request_rec * r);
 
+
 void ap_lua_rstack_dump(lua_State *L, request_rec *r, const char *msg)
 {
     int i;
     int top = lua_gettop(L);
-
     ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(01484) "Lua Stack Dump: [%s]", msg);
-
     for (i = 1; i <= top; i++) {
         int t = lua_type(L, i);
         switch (t) {
         case LUA_TSTRING:{
                 ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                               "%d:  '%s'", i, lua_tostring(L, i));
