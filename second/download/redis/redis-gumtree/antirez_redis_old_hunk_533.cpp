        else if (t == LUA_TUSERDATA) typename = "userdata";
        else if (t == LUA_TTHREAD) typename = "thread";
        else if (t == LUA_TLIGHTUSERDATA) typename = "light-userdata";
        s = sdscatprintf(s,"%s@%p",typename,p);
        }
        break;
    default:
        s = sdscat(s,"<unknown-lua-type>");
        break;
    }
    return s;
