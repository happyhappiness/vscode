                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                              "%d:  <function>", i);
                break;
            }
        default:{
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                              "%d:  unknown: -[%s]-", i, lua_typename(L, i));
                break;
            }
        }
    }
}

