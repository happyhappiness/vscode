    }
}

void sdsfreesplitres(sds *tokens, int count) {
    if (!tokens) return;
    while(count--)
        sdsfree(tokens[count]);
    zfree(tokens);
}

sds sdsfromlonglong(long long value) {
    char buf[32], *p;
    unsigned long long v;
