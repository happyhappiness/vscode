    dictRelease(server.lua_scripts);
    lua_close(server.lua);
}

void scriptingReset(void) {
    scriptingRelease();
    scriptingInit(0);
}

/* Set an array of Redis String Objects as a Lua array (table) stored into a
 * global variable. */
void luaSetGlobalArray(lua_State *lua, char *var, robj **elev, int elec) {
    int j;

    lua_newtable(lua);
    for (j = 0; j < elec; j++) {
        lua_pushlstring(lua,(char*)elev[j]->ptr,sdslen(elev[j]->ptr));
        lua_rawseti(lua,-2,j+1);
    }
    lua_setglobal(lua,var);
}

/* ---------------------------------------------------------------------------
 * Redis provided math.random
 * ------------------------------------------------------------------------- */

/* We replace math.random() with our implementation that is not affected
 * by specific libc random() implementations and will output the same sequence
 * (for the same seed) in every arch. */

/* The following implementation is the one shipped with Lua itself but with
 * rand() replaced by redisLrand48(). */
int redis_math_random (lua_State *L) {
  /* the `%' avoids the (rare) case of r==1, and is needed also because on
     some systems (SunOS!) `rand()' may return a value larger than RAND_MAX */
  lua_Number r = (lua_Number)(redisLrand48()%REDIS_LRAND48_MAX) /
                                (lua_Number)REDIS_LRAND48_MAX;
  switch (lua_gettop(L)) {  /* check number of arguments */
    case 0: {  /* no arguments */
      lua_pushnumber(L, r);  /* Number between 0 and 1 */
      break;
    }
    case 1: {  /* only upper limit */
      int u = luaL_checkint(L, 1);
      luaL_argcheck(L, 1<=u, 1, "interval is empty");
      lua_pushnumber(L, floor(r*u)+1);  /* int between 1 and `u' */
      break;
    }
    case 2: {  /* lower and upper limits */
      int l = luaL_checkint(L, 1);
      int u = luaL_checkint(L, 2);
      luaL_argcheck(L, l<=u, 2, "interval is empty");
      lua_pushnumber(L, floor(r*(u-l+1))+l);  /* int between `l' and `u' */
      break;
    }
    default: return luaL_error(L, "wrong number of arguments");
  }
  return 1;
}

int redis_math_randomseed (lua_State *L) {
  redisSrand48(luaL_checkint(L, 1));
  return 0;
}

/* ---------------------------------------------------------------------------
 * EVAL and SCRIPT commands implementation
 * ------------------------------------------------------------------------- */

/* Define a lua function with the specified function name and body.
 * The function name musts be a 42 characters long string, since all the
 * functions we defined in the Lua context are in the form:
 *
 *   f_<hex sha1 sum>
 *
 * On success C_OK is returned, and nothing is left on the Lua stack.
 * On error C_ERR is returned and an appropriate error is set in the
 * client context. */
int luaCreateFunction(client *c, lua_State *lua, char *funcname, robj *body) {
    sds funcdef = sdsempty();

    funcdef = sdscat(funcdef,"function ");
    funcdef = sdscatlen(funcdef,funcname,42);
    funcdef = sdscatlen(funcdef,"() ",3);
    funcdef = sdscatlen(funcdef,body->ptr,sdslen(body->ptr));
