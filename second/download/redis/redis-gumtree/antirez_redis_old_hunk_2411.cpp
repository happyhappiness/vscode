    sdsfree(o);
}

/* Rewrite a simple "option-name <bytes>" configuration option. */
void rewriteConfigBytesOption(struct rewriteConfigState *state, char *option, long long value, long long defvalue) {
    int force = value != defvalue;
    /* TODO: check if we can write it using MB, GB, or other suffixes. */
    sds line = sdscatprintf(sdsempty(),"%s %lld",option,value);

    rewriteConfigRewriteLine(state,option,line,force);
}

/* Rewrite a yes/no option. */
