static void lua_script_free(lua_script_t *script) /* {{{ */
{
  if (script == NULL)
    return;

  lua_script_t *next = script->next;

  if (script->lua_state != NULL) {
    lua_close(script->lua_state);
    script->lua_state = NULL;
  }

  sfree(script->script_path);
  sfree(script);

  lua_script_free(next);
}