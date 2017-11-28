krb5_error_code krb5_read_keytab(krb5_context context, char *name, krb5_kt_list *list)
{
    krb5_kt_list lp = NULL, tail = NULL, back = NULL;
    krb5_keytab kt;
    krb5_keytab_entry *entry;
    krb5_kt_cursor cursor;
    krb5_error_code retval = 0;

    if (*list) {
        /* point lp at the tail of the list */
        for (lp = *list; lp->next; lp = lp->next);
        back = lp;
    }
    retval = krb5_kt_resolve(context, name, &kt);
    if (check_k5_err(context, "krb5_kt_resolve", retval))
        return retval;
    retval = krb5_kt_start_seq_get(context, kt, &cursor);
    if (check_k5_err(context, "krb5_kt_start_seq_get", retval))
        goto close_kt;
    for (;;) {
        entry = (krb5_keytab_entry *)xcalloc(1, sizeof (krb5_keytab_entry));
        if (!entry) {
            retval = ENOMEM;
            debug((char *) "%s| %s: ERROR: krb5_read_keytab failed: %s\n",
                  LogTime(), PROGRAM, strerror(retval));
            fprintf(stderr, "%s| %s: ERROR: krb5_read_keytab: %s\n",
                    LogTime(), PROGRAM, strerror(retval));
            break;
        }
        memset(entry, 0, sizeof (*entry));
        retval = krb5_kt_next_entry(context, kt, entry, &cursor);
        if (check_k5_err(context, "krb5_kt_next_entry", retval))
            break;

        if (!lp) {              /* if list is empty, start one */
            lp = (krb5_kt_list)xmalloc(sizeof (*lp));
            if (!lp) {
                retval = ENOMEM;
                debug((char *) "%s| %s: ERROR: krb5_read_keytab failed: %s\n",
                      LogTime(), PROGRAM, strerror(retval));
                fprintf(stderr, "%s| %s: ERROR: krb5_read_keytab: %s\n",
                        LogTime(), PROGRAM, strerror(retval));
                break;
            }
        } else {
            lp->next = (krb5_kt_list)xmalloc(sizeof (*lp));
            if (!lp->next) {
                retval = ENOMEM;
                debug((char *) "%s| %s: ERROR: krb5_read_keytab failed: %s\n",
                      LogTime(), PROGRAM, strerror(retval));
                fprintf(stderr, "%s| %s: ERROR: krb5_read_keytab: %s\n",
                        LogTime(), PROGRAM, strerror(retval));
                break;
            }
            lp = lp->next;
        }
        if (!tail)
            tail = lp;
        lp->next = NULL;
        lp->entry = entry;
    }
    xfree(entry);
    if (retval) {
        if (retval == KRB5_KT_END)
            retval = 0;
        else {
            krb5_free_kt_list(context, tail);
            tail = NULL;
            if (back)
                back->next = NULL;
        }
    }
    if (!*list)
        *list = tail;
    krb5_kt_end_seq_get(context, kt, &cursor);
close_kt:
    krb5_kt_close(context, kt);
    return retval;
}