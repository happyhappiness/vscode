int luaC_pushvaluelist(lua_State *L, const data_set_t *ds,
                       const value_list_t *vl) /* {{{ */
{
  lua_newtable(L);

  lua_pushstring(L, vl->host);
  lua_setfield(L, -2, "host");

  lua_pushstring(L, vl->plugin);
  lua_setfield(L, -2, "plugin");
  lua_pushstring(L, vl->plugin_instance);
  lua_setfield(L, -2, "plugin_instance");

  lua_pushstring(L, vl->type);
  lua_setfield(L, -2, "type");
  lua_pushstring(L, vl->type_instance);
  lua_setfield(L, -2, "type_instance");

  luaC_pushvalues(L, ds, vl);
  lua_setfield(L, -2, "values");

  luaC_pushdstypes(L, ds);
  lua_setfield(L, -2, "dstypes");

  luaC_pushdsnames(L, ds);
  lua_setfield(L, -2, "dsnames");

  luaC_pushcdtime(L, vl->time);
  lua_setfield(L, -2, "time");

  luaC_pushcdtime(L, vl->interval);
  lua_setfield(L, -2, "interval");

  return 0;
}