    char *p = reply;

    switch(*p) {
    case ':':
        p = redisProtocolToLuaType_Int(lua,reply);
        break;
    case '$':
        p = redisProtocolToLuaType_Bulk(lua,reply);
        break;
    case '+':
        p = redisProtocolToLuaType_Status(lua,reply);
        break;
    case '-':
        p = redisProtocolToLuaType_Error(lua,reply);
        break;
    case '*':
        p = redisProtocolToLuaType_MultiBulk(lua,reply);
        break;
    }
    return p;
}
