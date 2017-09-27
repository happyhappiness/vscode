                searchptr = strchr(ctx->buffer, '>');
                if (searchptr != NULL)
                    *searchptr = ']';
            }

            filename = strrchr(ctx->buffer, ' ');
            *(filename++) = '\0';

            /* handle filenames with spaces in 'em */
            if (!strcmp(filename, ".") || !strcmp(filename, "..") || firstfile) {
                firstfile = 0;
                searchidx = filename - ctx->buffer;
