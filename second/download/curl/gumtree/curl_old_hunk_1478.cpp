
      /* new in libcurl 7.7: */
      curl_easy_setopt(curl, CURLOPT_RANDOM_FILE, config->random_file);
      curl_easy_setopt(curl, CURLOPT_EGDSOCKET, config->egd_file);
      curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, config->connecttimeout);

      /* debug */
      if(config->cipher_list)
        curl_easy_setopt(curl, CURLOPT_SSL_CIPHER_LIST, config->cipher_list);
      
      res = curl_easy_perform(curl);
        
      if(config->writeout) {
        ourWriteOut(curl, config->writeout);
      }

#ifdef	VMS
      if (!config->showerror)  {
        vms_show = VMSSTS_HIDE;
      }
#else
      if((res!=CURLE_OK) && config->showerror)
        fprintf(config->errors, "curl: (%d) %s\n", res, errorbuffer);
#endif

      if(config->headerfile && !headerfilep && heads.stream)
        fclose(heads.stream);

      if(urlbuffer)
        free(urlbuffer);
      if (outfile && !strequal(outfile, "-") && outs.stream)
        fclose(outs.stream);

#ifdef HAVE_UTIME
      /* Important that we set the time _after_ the file has been 
         closed, as is done above here */
