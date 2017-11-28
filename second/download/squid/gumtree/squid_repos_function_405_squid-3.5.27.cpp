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