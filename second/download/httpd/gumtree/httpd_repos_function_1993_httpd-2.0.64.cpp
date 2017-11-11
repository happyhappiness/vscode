static int getsfunc_STRING(char *w, int len, void *pvastrs)
{
    struct vastrs *strs = (struct vastrs*) pvastrs;
    const char *p;
    int t;
    
    if (!strs->curpos || !*strs->curpos) 
        return 0;
    p = ap_strchr_c(strs->curpos, '\n');
    if (p)
        ++p;
    else
        p = ap_strchr_c(strs->curpos, '\0');
    t = p - strs->curpos;
    if (t > len)
        t = len;
    strncpy (w, strs->curpos, t);
    w[t] = '\0';
    if (!strs->curpos[t]) {
        ++strs->arg;
        strs->curpos = va_arg(strs->args, const char *);
    }
    else
        strs->curpos += t;
    return t;    
}