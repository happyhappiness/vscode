static void extract_dn(apr_table_t *t, apr_hash_t *nids, const char *pfx,
                       X509_NAME *xn, apr_pool_t *p)
{
    STACK_OF(X509_NAME_ENTRY) *ents = xn->entries;
    X509_NAME_ENTRY *xsne;
    apr_hash_t *count;
    int i, nid;

    /* Hash of (int) NID -> (int *) counter to count each time an RDN
     * with the given NID has been seen. */
    count = apr_hash_make(p);

    /* For each RDN... */
    for (i = 0; i < sk_X509_NAME_ENTRY_num(ents); i++) {
         const char *tag;

         xsne = sk_X509_NAME_ENTRY_value(ents, i);

         /* Retrieve the nid, and check whether this is one of the nids
          * which are to be extracted. */
         nid = OBJ_obj2nid((ASN1_OBJECT *)X509_NAME_ENTRY_get_object(xsne));

         tag = apr_hash_get(nids, &nid, sizeof nid);
         if (tag) {
             const char *key;
             int *dup;
             char *value;

             /* Check whether a variable with this nid was already
              * been used; if so, use the foo_N=bar syntax. */
             dup = apr_hash_get(count, &nid, sizeof nid);
             if (dup) {
                 key = apr_psprintf(p, "%s%s_%d", pfx, tag, ++(*dup));
             }
             else {
                 /* Otherwise, use the plain foo=bar syntax. */
                 dup = apr_pcalloc(p, sizeof *dup);
                 apr_hash_set(count, &nid, sizeof nid, dup);
                 key = apr_pstrcat(p, pfx, tag, NULL);
             }
             value = modssl_X509_NAME_ENTRY_to_string(p, xsne);
             apr_table_setn(t, key, value);
         }
    }
}