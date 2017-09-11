    case LUA_TNUMBER:
        addReplyLongLong(c,(long long)lua_tonumber(lua,1));
        break;
    default:
        addReply(c,shared.nullbulk);
    }
