                    PROGRAM);
        return (1);
    }
    return (0);
}

#if HAVE_KRB5_MEMORY_KEYTAB
/*
 * Free a kt_list
 */
krb5_error_code krb5_free_kt_list(krb5_context context, krb5_kt_list list)
{
    krb5_kt_list lp = list;

    while (lp) {
#if USE_HEIMDAL_KRB5 || ( HAVE_KRB5_KT_FREE_ENTRY && HAVE_DECL_KRB5_KT_FREE_ENTRY )
        krb5_error_code  retval = krb5_kt_free_entry(context, lp->entry);
#else
        krb5_error_code  retval = krb5_free_keytab_entry_contents(context, lp->entry);
#endif
        safe_free(lp->entry);
        if (check_k5_err(context, "krb5_kt_free_entry", retval))
            return retval;
        krb5_kt_list prev = lp;
        lp = lp->next;
        xfree(prev);
    }
    return 0;
}
/*
 * Read in a keytab and append it to list.  If list starts as NULL,
 * allocate a new one if necessary.
 */
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

/*
 * Takes a kt_list and writes it to the named keytab.
 */
krb5_error_code krb5_write_keytab(krb5_context context, krb5_kt_list list, char *name)
{
    krb5_keytab kt;
    char ktname[MAXPATHLEN+sizeof("MEMORY:")+1];
    krb5_error_code retval = 0;

    snprintf(ktname, sizeof(ktname), "%s", name);
    retval = krb5_kt_resolve(context, ktname, &kt);
    if (retval)
        return retval;
    for (krb5_kt_list lp = list; lp; lp = lp->next) {
        retval = krb5_kt_add_entry(context, kt, lp->entry);
        if (retval)
            break;
    }
    /*
     *     krb5_kt_close(context, kt);
     */
    return retval;
}
#endif /* HAVE_KRB5_MEMORY_KEYTAB */

int
main(int argc, char *const argv[])
{
    char buf[MAX_AUTHTOKEN_LEN];
    char *c, *p;
    char *user = NULL;
    char *rfc_user = NULL;
#if HAVE_PAC_SUPPORT
    char ad_groups[MAX_PAC_GROUP_SIZE];
    char *ag=NULL;
    krb5_pac pac;
#if USE_HEIMDAL_KRB5
    gss_buffer_desc data_set = GSS_C_EMPTY_BUFFER;
#else
    gss_buffer_desc type_id = GSS_C_EMPTY_BUFFER;
#endif
#endif
    krb5_context context = NULL;
    krb5_error_code ret;
    long length = 0;
    static int err = 0;
    int opt, log = 0, norealm = 0;
    OM_uint32 ret_flags = 0, spnego_flag = 0;
    char *service_name = (char *) "HTTP", *host_name = NULL;
    char *token = NULL;
    char *service_principal = NULL;
    char *keytab_name = NULL;
    char *keytab_name_env = NULL;
    char default_keytab[MAXPATHLEN];
#if HAVE_KRB5_MEMORY_KEYTAB
    char *memory_keytab_name = NULL;
#endif
    char *rcache_type = NULL;
    char *rcache_type_env = NULL;
    char *rcache_dir = NULL;
    char *rcache_dir_env = NULL;
    OM_uint32 major_status, minor_status;
    gss_ctx_id_t gss_context = GSS_C_NO_CONTEXT;
    gss_name_t client_name = GSS_C_NO_NAME;
    gss_name_t server_name = GSS_C_NO_NAME;
    gss_cred_id_t server_creds = GSS_C_NO_CREDENTIAL;
    gss_buffer_desc service = GSS_C_EMPTY_BUFFER;
