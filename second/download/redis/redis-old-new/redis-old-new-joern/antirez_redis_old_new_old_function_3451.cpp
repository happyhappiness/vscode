static void printStringRepr(char *s, int len) {
    printf("\"");
    while(len--) {
        switch(*s) {
        case '\\':
        case '"':
            printf("\\%c",*s);
            break;
        case '\n': printf("\\n"); break;
        case '\r': printf("\\r"); break;
        case '\t': printf("\\t"); break;
        case '\a': printf("\\a"); break;
        case '\b': printf("\\b"); break;
        default:
            if (isprint(*s))
                printf("%c",*s);
            else
                printf("\\x%02x",(unsigned char)*s);
            break;
        }
        s++;
    }
    printf("\"");
}