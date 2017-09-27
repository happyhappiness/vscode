    lua_Debug dbg;

    lua_getstack(L, 1, &dbg);
    lua_getinfo(L, "Sl", &dbg);

    msg = luaL_checkstring(L, 2);
    ap_log_error(dbg.source, dbg.currentline, APLOG_MODULE_INDEX, level, 0,
                 cmd->server, "%s", msg);
    return 0;
}

/* r:debug(String) and friends which use apache logging */
