        addReplyErrorFormat(c,"Error running script (call to %s): %s\n",
            funcname, lua_tostring(lua,-1));
        lua_pop(lua,1);
        return;
    }
    selectDb(c,server.lua_client->db->id); /* set DB ID from Lua client */
    luaReplyToRedisReply(c,lua);
}
