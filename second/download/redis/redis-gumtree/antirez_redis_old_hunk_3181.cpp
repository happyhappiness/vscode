    case '+':
        p = redisProtocolToLuaType_Status(lua,reply);
        break;
    }
    return p;
}
