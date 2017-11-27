static int lua_shutdown(void) /* {{{ */
{
  lua_script_free(scripts);

  return (0);
}