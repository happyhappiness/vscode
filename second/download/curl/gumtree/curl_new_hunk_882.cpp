           * We have specified a file name to store the result in, or we have
           * decided we want to use the remote file name.
           */

          if(!outfile) {
            /* extract the file name from the URL */
            result = get_url_file_name(&outfile, this_url);
            if(result)
              goto show_error;
            if(!*outfile && !config->content_disposition) {
              helpf(global->errors, "Remote file name has no length!\n");
              result = CURLE_WRITE_ERROR;
              goto quit_urls;
            }
#if defined(MSDOS) || defined(WIN32)
            /* For DOS and WIN32, we do some major replacing of
               bad characters in the file name before using it */
            outfile = sanitize_dos_name(outfile);
            if(!outfile) {
              result = CURLE_OUT_OF_MEMORY;
              goto show_error;
            }
#endif /* MSDOS || WIN32 */
          }
          else if(urls) {
            /* fill '#1' ... '#9' terms from URL pattern */
            char *storefile = outfile;
            result = glob_match_url(&outfile, storefile, urls);
            Curl_safefree(storefile);
            if(result) {
              /* bad globbing */
              warnf(config, "bad output glob!\n");
              goto quit_urls;
            }
          }

          /* Create the directory hierarchy, if not pre-existent to a multiple
             file output call */

          if(config->create_dirs || metalink) {
            result = create_dir_hierarchy(outfile, global->errors);
            /* create_dir_hierarchy shows error upon CURLE_WRITE_ERROR */
            if(result == CURLE_WRITE_ERROR)
              goto quit_urls;
            if(result) {
              goto show_error;
            }
          }

          if((urlnode->flags & GETOUT_USEREMOTE)
             && config->content_disposition) {
