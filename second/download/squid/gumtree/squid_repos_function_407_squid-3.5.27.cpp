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