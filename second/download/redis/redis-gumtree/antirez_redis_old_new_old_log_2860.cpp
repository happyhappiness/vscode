addReplyErrorFormat(c,"Error running script (new function): %s\n",
                lua_tostring(lua,-1));