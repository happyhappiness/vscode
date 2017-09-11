        char *obj_s;
        size_t obj_len;

        obj_s = (char*)lua_tolstring(lua,j+1,&obj_len);
        if (obj_s == NULL) break; /* Not a string. */

        /* Try to use a cached object. */
        if (j < LUA_CMD_OBJCACHE_SIZE && cached_objects[j] && 
            cached_objects_len[j] >= obj_len) 
        {
            char *s = cached_objects[j]->ptr;
            struct sdshdr *sh = (void*)(s-(sizeof(struct sdshdr)));
