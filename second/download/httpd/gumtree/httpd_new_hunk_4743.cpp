    {"match_handler", cfg_lua_map_handler},
    {"directory", cfg_directory},
    /* {"root", cfg_root}, */
    {NULL, NULL}
};

/* helper function for the logging functions below */
static int cmd_log_at(lua_State *L, int level)
{
    const char *msg;
    cmd_parms *cmd = check_cmd_parms(L, 1);
    lua_Debug dbg;
