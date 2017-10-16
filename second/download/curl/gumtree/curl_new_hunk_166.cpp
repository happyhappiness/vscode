            /* fill '#1' ... '#9' terms from URL pattern */
            char *storefile = outfile;
            outfile = glob_match_url(storefile, urls);
            free(storefile);
            if(!outfile) {
              /* bad globbing */
              warnf(config, "bad output glob!\n");
              free(url);
              res = CURLE_FAILED_INIT;
              break;
            }
          }

