        if (value == enum_val) matching_name = enum_name;
    }
    va_end(ap);

    force = value != def_val;
    line = sdscatprintf(sdsempty(),"%s %s",option,matching_name);
    rewriteConfigRewriteLine(state,option,line,force);
