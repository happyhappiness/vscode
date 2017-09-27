{
    return lua_ssl_is_https ? lua_ssl_is_https(c) : 0;
}

/*******************************/

command_rec lua_commands[] = {

    AP_INIT_TAKE1("LuaRoot", register_lua_root, NULL, OR_ALL,
                  "Specify the base path for resolving relative paths for mod_lua directives"),

    AP_INIT_TAKE1("LuaPackagePath", register_package_dir, NULL, OR_ALL,
                  "Add a directory to lua's package.path"),

    AP_INIT_TAKE1("LuaPackageCPath", register_package_cdir, NULL, OR_ALL,
                  "Add a directory to lua's package.cpath"),


    AP_INIT_TAKE23("LuaHookTranslateName", register_translate_name_hook, NULL,
                  OR_ALL,
                  "Provide a hook for the translate name phase of request processing"),

    AP_INIT_RAW_ARGS("<LuaHookTranslateName", register_translate_name_block,
