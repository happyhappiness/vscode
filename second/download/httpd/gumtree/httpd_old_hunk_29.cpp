            /*
             * Now recurse these... we handle errors and subdirectories
             * via the recursion, which is nice
             */
            for (current = 0; current < candidates->nelts; ++current) {
                fnew = &((fnames *) candidates->elts)[current];
                fprintf(stderr, " Processing config file: %s\n", fnew->fname);
                ap_process_resource_config(s, fnew->fname, conftree, p, ptemp);
            }
        }

        return;
    }
