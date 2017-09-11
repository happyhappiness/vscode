            addReplyErrorFormat(c,"Error compiling script (new function): %s\n",
                lua_tostring(lua,-1));
            lua_pop(lua,1);
            sdsfree(funcdef);
            return;
        }
        sdsfree(funcdef);
        if (lua_pcall(lua,0,0,0)) {
            addReplyErrorFormat(c,"Error running script (new function): %s\n",
                lua_tostring(lua,-1));
