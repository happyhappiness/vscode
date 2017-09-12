luaL_error(l, "Cannot serialise, excessive nesting (%d)",
                   cfg->current_depth);