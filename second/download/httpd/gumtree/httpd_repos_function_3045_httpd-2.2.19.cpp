static apr_status_t apr_xml_parser_convert_elem(apr_xml_elem *e,
                                                apr_xlate_t *convset)
{
    apr_xml_attr *a;
    apr_xml_elem *ec;
    apr_text *t;
    apr_size_t inbytes_left, outbytes_left;
    apr_status_t status;

    inbytes_left = outbytes_left = strlen(e->name);
    status = apr_xlate_conv_buffer(convset, e->name,  &inbytes_left, (char *) e->name, &outbytes_left);
    if (status) {
        return status;
    }

    for (t = e->first_cdata.first; t != NULL; t = t->next) {
        inbytes_left = outbytes_left = strlen(t->text);
        status = apr_xlate_conv_buffer(convset, t->text, &inbytes_left, (char *) t->text, &outbytes_left);
        if (status) {
            return status;
        }
    }

    for (t = e->following_cdata.first;  t != NULL; t = t->next) {
        inbytes_left = outbytes_left = strlen(t->text);
        status = apr_xlate_conv_buffer(convset, t->text, &inbytes_left, (char *) t->text, &outbytes_left);
        if (status) {
            return status;
        }
    }

    for (a = e->attr; a != NULL; a = a->next) {
        inbytes_left = outbytes_left = strlen(a->name);
        status = apr_xlate_conv_buffer(convset, a->name, &inbytes_left, (char *) a->name, &outbytes_left);
        if (status) {
            return status;
        }
        inbytes_left = outbytes_left = strlen(a->value);
        status = apr_xlate_conv_buffer(convset, a->value, &inbytes_left, (char *) a->value, &outbytes_left);
        if (status) {
            return status;
        }
    }

    for (ec = e->first_child; ec != NULL; ec = ec->next) {
        status = apr_xml_parser_convert_elem(ec, convset);
        if (status) {
            return status;
        }
    }
    return APR_SUCCESS;
}