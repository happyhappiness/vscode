
          if(!outfile) {
            /* extract the file name from the URL */
            result = get_url_file_name(&outfile, this_url);
            if(result)
              goto show_error;

#if defined(MSDOS) || defined(WIN32)
            result = sanitize_file_name(&outfile);
            if(result) {
              Curl_safefree(outfile);
              goto show_error;
            }
#endif /* MSDOS || WIN32 */

            if(!*outfile && !config->content_disposition) {
              helpf(global->errors, "Remote file name has no length!\n");
              result = CURLE_WRITE_ERROR;
              goto quit_urls;
            }
          }
          else if(urls) {
            /* fill '#1' ... '#9' terms from URL pattern */
            char *storefile = outfile;
            result = glob_match_url(&outfile, storefile, urls);
            Curl_safefree(storefile);

#if defined(MSDOS) || defined(WIN32)
            if(!result) {
              result = sanitize_file_name(&outfile);
              if(result) {
                Curl_safefree(outfile);
                goto show_error;
              }
            }
#endif /* MSDOS || WIN32 */

            if(result) {
              /* bad globbing */
              warnf(config->global, "bad output glob!\n");
              goto quit_urls;
            }
          }
