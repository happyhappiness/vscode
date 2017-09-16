

    while (1) {

        if (!(tag_val = get_tag(r->pool, in, tag, sizeof(tag), 1))) {

            return 1;

        }

        if (!strcmp(tag, "var")) {

            const char *val = ap_table_get(r->subprocess_env, tag_val);



            if (val) {

                ap_rputs(val, r);

            }

            else {

                ap_rputs("(none)", r);

