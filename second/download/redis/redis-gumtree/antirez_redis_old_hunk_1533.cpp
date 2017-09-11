    rewriteConfigRewriteLine(state,option,line,force);
}

/* Rewrite an enumeration option, after the "value" every enum/value pair
 * is specified, terminated by NULL. After NULL the default value is
 * specified. See how the function is used for more information. */
void rewriteConfigEnumOption(struct rewriteConfigState *state, char *option, int value, ...) {
    va_list ap;
    char *enum_name, *matching_name = NULL;
    int enum_val, def_val, force;
    sds line;

    va_start(ap, value);
    while(1) {
        enum_name = va_arg(ap,char*);
        enum_val = va_arg(ap,int);
        if (enum_name == NULL) {
            def_val = enum_val;
            break;
        }
        if (value == enum_val) matching_name = enum_name;
    }
    va_end(ap);

    force = value != def_val;
    line = sdscatprintf(sdsempty(),"%s %s",option,matching_name);
    rewriteConfigRewriteLine(state,option,line,force);
}

