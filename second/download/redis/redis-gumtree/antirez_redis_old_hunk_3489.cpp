                out = sdscatprintf(out,_prefixfmt,i == 0 ? "" : prefix,i+1);

                /* Format the multi bulk entry */
                tmp = cliFormatReply(r->element[i],_prefix);
                out = sdscatlen(out,tmp,sdslen(tmp));
                sdsfree(tmp);
            }
