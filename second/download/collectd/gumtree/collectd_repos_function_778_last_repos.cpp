int luaC_tostringbuffer(lua_State *L, int idx, /* {{{ */
                        char *buffer, size_t buffer_size) {
  const char *str = lua_tostring(L, idx);
  if (str == NULL)
    return -1;

  sstrncpy(buffer, str, buffer_size);
  return 0;
}