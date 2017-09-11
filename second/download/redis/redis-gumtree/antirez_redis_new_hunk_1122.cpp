            lua_tostring(lua,-1));
        lua_pop(lua,1);
        sdsfree(funcdef);
        return C_ERR;
    }
    sdsfree(funcdef);
    if (lua_pcall(lua,0,0,0)) {
        addReplyErrorFormat(c,"Error running script (new function): %s\n",
            lua_tostring(lua,-1));
        lua_pop(lua,1);
        return C_ERR;
    }

    /* We also save a SHA1 -> Original script map in a dictionary
