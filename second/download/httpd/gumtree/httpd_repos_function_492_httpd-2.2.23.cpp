static int getvalue(server_rec *s, struct magic *m, char **p)
{
    int slen;

    if (m->type == STRING) {
        *p = getstr(s, *p, m->value.s, sizeof(m->value.s), &slen);
        m->vallen = slen;
    }
    else if (m->reln != 'x')
        m->value.l = signextend(s, m, strtol(*p, p, 0));
    return 0;
}