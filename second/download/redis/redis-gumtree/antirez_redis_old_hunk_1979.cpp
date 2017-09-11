    for (j = 0; j < argc; j++) {
        char *obj_s;
        size_t obj_len;

        if (lua_isnumber(lua,j+1)) {
            /* We can't use lua_tolstring() for number -> string conversion
             * since Lua uses a format specifier that loses precision. */
            char dbuf[64];
            lua_Number num = lua_tonumber(lua,j+1);

            obj_len = snprintf(dbuf,sizeof(dbuf),"%.17g",(double)num);
