        } else {
            goto badfmt;
        }
    } else if (!strcasecmp(c->argv[2]->ptr,"client-output-buffer-limit")) {
        int vlen, j;
        sds *v = sdssplitlen(o->ptr,sdslen(o->ptr)," ",1,&vlen);

        /* We need a multiple of 4: <class> <hard> <soft> <soft_seconds> */
        if (vlen % 4) {
            sdsfreesplitres(v,vlen);
            goto badfmt;
        }

        /* Sanity check of single arguments, so that we either refuse the
         * whole configuration string or accept it all, even if a single
         * error in a single client class is present. */
        for (j = 0; j < vlen; j++) {
            char *eptr;
            long val;

            if ((j % 4) == 0) {
                if (getClientLimitClassByName(v[j]) == -1) {
                    sdsfreesplitres(v,vlen);
                    goto badfmt;
                }
            } else {
                val = strtoll(v[j], &eptr, 10);
                if (eptr[0] != '\0' || val < 0) {
                    sdsfreesplitres(v,vlen);
                    goto badfmt;
                }
            }
        }
        /* Finally set the new config */
        for (j = 0; j < vlen; j += 4) {
            int class;
            unsigned long long hard, soft;
            int soft_seconds;

            class = getClientLimitClassByName(v[j]);
            hard = strtoll(v[j+1],NULL,10);
            soft = strtoll(v[j+2],NULL,10);
            soft_seconds = strtoll(v[j+3],NULL,10);

            server.client_obuf_limits[class].hard_limit_bytes = hard;
            server.client_obuf_limits[class].soft_limit_bytes = soft;
            server.client_obuf_limits[class].soft_limit_seconds = soft_seconds;
        }
        sdsfreesplitres(v,vlen);

    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
