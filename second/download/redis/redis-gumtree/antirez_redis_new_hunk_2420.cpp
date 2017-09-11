    rewriteConfigRewriteLine(state,option,line,force);
}

/* Rewrite a numerical (long long range) option. */
void rewriteConfigNumericalOption(struct rewriteConfigState *state, char *option, long long value, long long defvalue) {
    int force = value != defvalue;
    sds line = sdscatprintf(sdsempty(),"%s %lld",option,value);

    rewriteConfigRewriteLine(state,option,line,force);
}

/* Rewrite a octal option. */
void rewriteConfigOctalOption(struct rewriteConfigState *state, char *option, int value, int defvalue) {
    int force = value != defvalue;
    sds line = sdscatprintf(sdsempty(),"%s %o",option,value);

    rewriteConfigRewriteLine(state,option,line,force);
}

/* Rewrite an enumeration option, after the "value" every enum/value pair
 * is specified, terminated by NULL. After NULL the default value is
 * specified. See how the function is used for more information. */
void rewriteConfigEnumOption(struct rewriteConfigState *state, char *option, int value, ...) {
    va_list ap;
    char *enum_name, *matching_name;
