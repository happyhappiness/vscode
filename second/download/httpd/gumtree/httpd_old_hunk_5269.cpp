 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mod_lua.h"
#include "lua_apr.h"

apr_table_t *ap_lua_check_apr_table(lua_State *L, int index)
{
    apr_table_t *t;
    luaL_checkudata(L, index, "Apr.Table");
    t = lua_unboxpointer(L, index);
    return t;
}


void ap_lua_push_apr_table(lua_State *L, apr_table_t *t)
{
    lua_boxpointer(L, t);
    luaL_getmetatable(L, "Apr.Table");
    lua_setmetatable(L, -2);
}

static int lua_table_set(lua_State *L)
{
    apr_table_t    *t = ap_lua_check_apr_table(L, 1);
    const char     *key = luaL_checkstring(L, 2);
    const char     *val = luaL_checkstring(L, 3);

    apr_table_set(t, key, val);
    return 0;
}

static int lua_table_get(lua_State *L)
{
    apr_table_t    *t = ap_lua_check_apr_table(L, 1);
    const char     *key = luaL_checkstring(L, 2);
    const char     *val = apr_table_get(t, key);
    lua_pushstring(L, val);
    return 1;
}

static const luaL_Reg lua_table_methods[] = {
    {"set", lua_table_set},
