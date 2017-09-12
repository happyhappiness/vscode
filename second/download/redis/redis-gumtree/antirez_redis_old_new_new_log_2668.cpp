addReplyErrorFormat(c,"Error compiling script (new function): %s\n",
            lua_tostring(lua,-1));