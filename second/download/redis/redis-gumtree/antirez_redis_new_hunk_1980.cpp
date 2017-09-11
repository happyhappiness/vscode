        char *obj_s;
        size_t obj_len;

        if (lua_isnumber(lua,j+1)) {
            /* We can't use lua_tolstring() for number -> string conversion
             * since Lua uses a format specifier that loses precision. */
            char dbuf[64];
            lua_Number num = lua_tonumber(lua,j+1);

            obj_len = snprintf(dbuf,sizeof(dbuf),"%.17g",(double)num);
            obj_s = dbuf;
        } else {
            obj_s = (char*)lua_tolstring(lua,j+1,&obj_len);
            if (obj_s == NULL) break; /* Not a string. */
        }

        /* Try to use a cached object. */
        if (j < LUA_CMD_OBJCACHE_SIZE && cached_objects[j] &&
            cached_objects_len[j] >= obj_len)
        {
            char *s = cached_objects[j]->ptr;
            struct sdshdr *sh = (void*)(s-(sizeof(struct sdshdr)));
