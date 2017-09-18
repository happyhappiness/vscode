
    if (namespaces != NULL) {
       int i;

       for (i = namespaces->nelts; i--; ) {
           ap_rprintf(r, " xmlns:ns%d=\"%s\"", i,
                      AP_XML_GET_URI_ITEM(namespaces, i));
       }
    }

    /* ap_rputc('>', r); */
    ap_rputs(">" DEBUG_CR, r);

    for (; first != NULL; first = first->next) {
        ap_text *t;

        if (first->propresult.xmlns == NULL) {
            ap_rputs("<D:response>", r);
        }
        else {
            ap_rputs("<D:response", r);
