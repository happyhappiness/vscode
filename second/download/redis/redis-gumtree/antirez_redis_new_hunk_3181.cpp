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
