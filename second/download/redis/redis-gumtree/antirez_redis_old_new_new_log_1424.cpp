luaL_error(l, "Found too many nested data structures (%d) at character %d",
        json->current_depth, json->ptr - json->data);