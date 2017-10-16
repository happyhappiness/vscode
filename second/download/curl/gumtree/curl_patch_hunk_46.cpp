     }
 
     /* default output stream is stdout */
     outs.stream = stdout;
     outs.config = config;
 
-    if(!config->globoff) {
-      /* Unless explicitly shut off, we expand '{...}' and '[...]' expressions
-         and return total number of URLs in pattern set */
-      res = glob_url(&urls, url, &urlnum);
-      if(res != CURLE_OK)
-        return res;
-    }
-
-
     /* save outfile pattern before expansion */
     outfiles = urlnode->outfile?strdup(urlnode->outfile):NULL;
 
-    if ((!outfiles || curl_strequal(outfiles, "-")) && urlnum > 1) {
-      /* multiple files extracted to stdout, insert separators! */
-      separator = 1;
-    }
-    for(i = 0;
-        (url = urls?next_url(urls):(i?NULL:strdup(url)));
-        i++) {
-      char *outfile;
-      outfile = outfiles?strdup(outfiles):NULL;
- 
-      if((urlnode->flags&GETOUT_USEREMOTE) ||
-         (outfile && !curl_strequal("-", outfile)) ) {
+    infiles = urlnode->infile;
 
-        /* 
-         * We have specified a file name to store the result in, or we have
-         * decided we want to use the remote file name.
-         */
+    if(!config->globoff && infiles) {
+      /* Unless explicitly shut off */
+      res = glob_url(&inglob, infiles, &infilenum,
+                     config->showerror?
+                     (config->errors?config->errors:stderr):NULL);
+      if(res != CURLE_OK) {
+        clean_getout(config);
+        break;
+      }
+    }
+
+    /* Here's the loop for uploading multiple files within the same
+       single globbed string. If no upload, we enter the loop once anyway. */
+    for(up = 0;
+        (!up && !infiles) ||
+          (uploadfile = inglob?
+           glob_next_url(inglob):
+           (!up?strdup(infiles):NULL));
+        up++) {
+      uploadfilesize=-1;
+
+      if(!config->globoff) {
+        /* Unless explicitly shut off, we expand '{...}' and '[...]'
+           expressions and return total number of URLs in pattern set */
+        res = glob_url(&urls, dourl, &urlnum,
+                       config->showerror?
+                       (config->errors?config->errors:stderr):NULL);
+        if(res != CURLE_OK) {
+          break;
+        }
+      }
+      else
+        urlnum = 1; /* without globbing, this is a single URL */
+
+      /* if multiple files extracted to stdout, insert separators! */
+      separator= ((!outfiles || curl_strequal(outfiles, "-")) && urlnum > 1);
+
+      /* Here's looping around each globbed URL */
+      for(i = 0;
+          (url = urls?glob_next_url(urls):(i?NULL:strdup(url)));
+          i++) {
+        char *outfile;
+        outfile = outfiles?strdup(outfiles):NULL;
+        
+        if((urlnode->flags&GETOUT_USEREMOTE) ||
+           (outfile && !curl_strequal("-", outfile)) ) {
+          
+          /* 
+           * We have specified a file name to store the result in, or we have
+           * decided we want to use the remote file name.
+           */
       
-        if(!outfile) {
-          /* Find and get the remote file name */
-          char * pc =strstr(url, "://");
-          if(pc)
-            pc+=3;
-          else
-            pc=url;
-          pc = strrchr(pc, '/');
-          outfile = (char *) NULL == pc ? NULL : strdup(pc+1) ;
           if(!outfile) {
-            helpf("Remote file name has no length!\n");
-            return CURLE_WRITE_ERROR;
+            /* Find and get the remote file name */
+            char * pc =strstr(url, "://");
+            if(pc)
+              pc+=3;
+            else
+              pc=url;
+            pc = strrchr(pc, '/');
+
+            if(pc) {
+              /* duplicate the string beyond the slash */
+              pc++;
+              outfile = *pc ? strdup(pc): NULL;
+            }
+            if(!outfile || !*outfile) {
+              helpf("Remote file name has no length!\n");
+              res = CURLE_WRITE_ERROR;
+              free(url);
+              break;
+            }
+#if defined(__DJGPP__)
+            {
+              /* This is for DOS, and then we do some major replacing of 
+                 bad characters in the file name before using it */
+              char *file1=xmalloc(PATH_MAX);
+              strcpy(file1, msdosify(outfile));
+              strcpy(outfile, rename_if_dos_device_name(file1));
+              xfree(file1);
+            }
+#endif /* __DJGPP__ */
           }
-        }
-        else if(urls) {
-          /* fill '#1' ... '#9' terms from URL pattern */
-          char *storefile = outfile;
-          outfile = match_url(storefile, urls);
-          free(storefile);
-        }
-      
-        /* Create the directory hierarchy, if not pre-existant to a multiple
-           file output call */
-        
-        if(config->create_dirs)
-          if (-1 == create_dir_hierarchy(outfile))
-            return CURLE_WRITE_ERROR;
+          else if(urls) {
+            /* fill '#1' ... '#9' terms from URL pattern */
+            char *storefile = outfile;
+            outfile = glob_match_url(storefile, urls);
+            free(storefile);
+            if(!outfile) {
+              /* bad globbing */
+              fprintf(stderr, "bad output glob!\n");
+              free(url);
+              res = CURLE_FAILED_INIT;
+              break;
+            }
+          }
+          
+          /* Create the directory hierarchy, if not pre-existant to a multiple
+             file output call */
         
-        if(config->resume_from_current) {
-          /* We're told to continue from where we are now. Get the
-             size of the file as it is now and open it for append instead */
+          if(config->create_dirs)
+            if (-1 == create_dir_hierarchy(outfile)) {
+              return CURLE_WRITE_ERROR;
+            }
           
-          struct stat fileinfo;
+          if(config->resume_from_current) {
+            /* We're told to continue from where we are now. Get the
+               size of the file as it is now and open it for append instead */
+            
+            struct stat fileinfo;
 
-          /*VMS?? -- Danger, the filesize is only valid for stream files */
-          if(0 == stat(outfile, &fileinfo))
-            /* set offset to current file size: */
-            config->resume_from = fileinfo.st_size;
-          else
-            /* let offset be 0 */
-            config->resume_from = 0;
-        }
+            /*VMS?? -- Danger, the filesize is only valid for stream files */
+            if(0 == stat(outfile, &fileinfo))
+              /* set offset to current file size: */
+              config->resume_from = fileinfo.st_size;
+            else
+              /* let offset be 0 */
+              config->resume_from = 0;
+          }
         
-        if(config->resume_from) {
-          /* open file for output: */
-          outs.stream=(FILE *) fopen(outfile, config->resume_from?"ab":"wb");
-          if (!outs.stream) {
-            helpf("Can't open '%s'!\n", outfile);
-            return CURLE_WRITE_ERROR;
+          if(config->resume_from) {
+            /* open file for output: */
+            outs.stream=(FILE *) fopen(outfile, config->resume_from?"ab":"wb");
+            if (!outs.stream) {
+              helpf("Can't open '%s'!\n", outfile);
+              return CURLE_WRITE_ERROR;
+            }
+          }
+          else {
+            outs.filename = outfile;
+            outs.stream = NULL; /* open when needed */
           }
         }
-        else {
-          outs.filename = outfile;
-          outs.stream = NULL; /* open when needed */
-        }
-      }
-      if(config->infile) {
-        /*
-         * We have specified a file to upload
-         */
-        struct stat fileinfo;
+        infdfopen=FALSE;
+        if(uploadfile && !curl_strequal(uploadfile, "-")) {
+          /*
+           * We have specified a file to upload and it isn't "-".
+           */
+          struct stat fileinfo;
 
-        /* If no file name part is given in the URL, we add this file name */
-        char *ptr=strstr(url, "://");
-        if(ptr)
-          ptr+=3;
-        else
-          ptr=url;
-        ptr = strrchr(ptr, '/');
-        if(!ptr || !strlen(++ptr)) {
-          /* The URL has no file name part, add the local file name. In order
-             to be able to do so, we have to create a new URL in another
-             buffer.*/
-
-          /* We only want the part of the local path that is on the right
-             side of the rightmost slash and backslash. */
-          char *filep = strrchr(config->infile, '/');
-          char *file2 = strrchr(filep?filep:config->infile, '\\');
-
-          if(file2)
-            filep = file2+1;
-          else if(filep)
-            filep++;
+          /* If no file name part is given in the URL, we add this file name */
+          char *ptr=strstr(url, "://");
+          if(ptr)
+            ptr+=3;
           else
-            filep = config->infile;
+            ptr=url;
+          ptr = strrchr(ptr, '/');
+          if(!ptr || !strlen(++ptr)) {
+            /* The URL has no file name part, add the local file name. In order
+               to be able to do so, we have to create a new URL in another
+               buffer.*/
+
+            /* We only want the part of the local path that is on the right
+               side of the rightmost slash and backslash. */
+            char *filep = strrchr(uploadfile, '/');
+            char *file2 = strrchr(filep?filep:uploadfile, '\\');
+
+            if(file2)
+              filep = file2+1;
+            else if(filep)
+              filep++;
+            else
+              filep = uploadfile;
 
-          /* URL encode the file name */
-          filep = curl_escape(filep, 0 /* use strlen */);
+            /* URL encode the file name */
+            filep = curl_escape(filep, 0 /* use strlen */);
 
-          if(filep) {
+            if(filep) {
 
-            urlbuffer=(char *)malloc(strlen(url) + strlen(filep) + 3);
-            if(!urlbuffer) {
-              helpf("out of memory\n");
-              return CURLE_OUT_OF_MEMORY;
-            }
-            if(ptr)
-              /* there is a trailing slash on the URL */
-              sprintf(urlbuffer, "%s%s", url, filep);
-            else
-              /* thers is no trailing slash on the URL */
-              sprintf(urlbuffer, "%s/%s", url, filep);
+              urlbuffer=(char *)malloc(strlen(url) + strlen(filep) + 3);
+              if(!urlbuffer) {
+                helpf("out of memory\n");
+                return CURLE_OUT_OF_MEMORY;
+              }
+              if(ptr)
+                /* there is a trailing slash on the URL */
+                sprintf(urlbuffer, "%s%s", url, filep);
+              else
+                /* thers is no trailing slash on the URL */
+                sprintf(urlbuffer, "%s/%s", url, filep);
             
-            curl_free(filep);
+              curl_free(filep);
 
-            free(url);
-            url = urlbuffer; /* use our new URL instead! */
+              free(url);
+              url = urlbuffer; /* use our new URL instead! */
+            }
           }
-        }
 /*VMS??-- Reading binary from files can be a problem... */
 /*VMS??   Only FIXED, VAR etc WITHOUT implied CC will work */
 /*VMS??   Others need a \n appended to a line */
 /*VMS??-- Stat gives a size but this is UNRELIABLE in VMS */
 /*VMS??   As a f.e. a fixed file with implied CC needs to have a byte added */
 /*VMS??   for every record processed, this can by derived from Filesize & recordsize */
 /*VMS??   for VARiable record files the records need to be counted! */
 /*VMS??   for every record add 1 for linefeed and subtract 2 for the record header */
 /*VMS??   for VARIABLE header files only the bare record data needs to be considered with one appended if implied CC */
 
-        infd=(FILE *) fopen(config->infile, "rb");
-        if (!infd || stat(config->infile, &fileinfo)) {
-          helpf("Can't open '%s'!\n", config->infile);
-          return CURLE_READ_ERROR;
-        }
-        infilesize=fileinfo.st_size;
+          infd=(FILE *) fopen(uploadfile, "rb");
+          if (!infd || stat(uploadfile, &fileinfo)) {
+            helpf("Can't open '%s'!\n", uploadfile);
+            return CURLE_READ_ERROR;
+          }
+          infdfopen=TRUE;
+          uploadfilesize=fileinfo.st_size;
       
-      }
-      if((config->conf&CONF_UPLOAD) &&
-         config->resume_from_current) {
-        config->resume_from = -1; /* -1 will then force get-it-yourself */
-      }
-      if(outs.stream && isatty(fileno(outs.stream)) &&
-         !(config->conf&(CONF_UPLOAD|CONF_HTTPPOST)))
-        /* we send the output to a tty and it isn't an upload operation,
-           therefore we switch off the progress meter */
-        config->conf |= CONF_NOPROGRESS;
-    
+        }
+        else if(uploadfile && curl_strequal(uploadfile, "-")) {
+          infd = stdin;
+        }
 
-      if (urlnum > 1 && !(config->conf&CONF_MUTE)) {
-        fprintf(stderr, "\n[%d/%d]: %s --> %s\n",
-                i+1, urlnum, url, outfile ? outfile : "<stdout>");
-        if (separator)
-          printf("%s%s\n", CURLseparator, url);
-      }
-      if (httpgetfields) {
-        /* Find out whether the url contains a file name */
-        char *pc =strstr(url, "://");
-        char separator='?';
-        if(pc)
-          pc+=3;
-        else
-          pc=url;
+        if(uploadfile && config->resume_from_current)
+          config->resume_from = -1; /* -1 will then force get-it-yourself */
+
+        if(outs.stream && isatty(fileno(outs.stream)))
+          /* we send the output to a tty, therefore we switch off the progress
+             meter */
+          config->conf |= CONF_NOPROGRESS;
+
+        if (urlnum > 1 && !(config->conf&CONF_MUTE)) {
+          fprintf(stderr, "\n[%d/%d]: %s --> %s\n",
+                  i+1, urlnum, url, outfile ? outfile : "<stdout>");
+          if (separator)
+            printf("%s%s\n", CURLseparator, url);
+        }
+        if (httpgetfields) {
+          /* Find out whether the url contains a file name */
+          char *pc =strstr(url, "://");
+          char separator='?';
+          if(pc)
+            pc+=3;
+          else
+            pc=url;
 
-        pc = strrchr(pc, '/'); /* check for a slash */
+          pc = strrchr(pc, '/'); /* check for a slash */
 
-        if(pc) {
-          /* there is a slash present in the URL */
+          if(pc) {
+            /* there is a slash present in the URL */
 
-          if(strchr(pc, '?'))
-          /* Ouch, there's already a question mark in the URL string, we
-             then appead the data with an amperand separator instead! */
-            separator='&';
-        }
-        /*
-         * Then append ? followed by the get fields to the url.
-         */
-        urlbuffer=(char *)malloc(strlen(url) + strlen(httpgetfields) + 2);
-        if(!urlbuffer) {
-          helpf("out of memory\n");
-          return CURLE_OUT_OF_MEMORY;
-        }
-        if (pc)
-          sprintf(urlbuffer, "%s%c%s", url, separator, httpgetfields);
-        else
-          /* Append  / before the ? to create a well-formed url
-             if the url contains a hostname only
-          */
-          sprintf(urlbuffer, "%s/?%s", url, httpgetfields);
+            if(strchr(pc, '?'))
+              /* Ouch, there's already a question mark in the URL string, we
+                 then appead the data with an amperand separator instead! */
+              separator='&';
+          }
+          /*
+           * Then append ? followed by the get fields to the url.
+           */
+          urlbuffer=(char *)malloc(strlen(url) + strlen(httpgetfields) + 2);
+          if(!urlbuffer) {
+            helpf("out of memory\n");
+            return CURLE_OUT_OF_MEMORY;
+          }
+          if (pc)
+            sprintf(urlbuffer, "%s%c%s", url, separator, httpgetfields);
+          else
+            /* Append  / before the ? to create a well-formed url
+               if the url contains a hostname only
+            */
+            sprintf(urlbuffer, "%s/?%s", url, httpgetfields);
  
-        free(url); /* free previous URL */
-        url = urlbuffer; /* use our new URL instead! */
-      }
+          free(url); /* free previous URL */
+          url = urlbuffer; /* use our new URL instead! */
+        }
 
-      if(!config->errors)
-        config->errors = stderr;
+        if(!config->errors)
+          config->errors = stderr;
 
-#if defined(WIN32) && !defined(__CYGWIN32__)
-      if(!outfile && !(config->conf & CONF_GETTEXT)) {
-        /* We get the output to stdout and we have not got the ASCII/text flag,
-           then set stdout to be binary */
-        setmode( 1, O_BINARY );
-      }
+#ifdef O_BINARY
+        if(!outfile && !(config->conf & CONF_GETTEXT)) {
+          /* We get the output to stdout and we have not got the ASCII/text flag,
+             then set stdout to be binary */
+          setmode( fileno(stdout), O_BINARY );
+        }
 #endif
 
-      curl_easy_setopt(curl, CURLOPT_SSLENGINE, config->engine);
-      curl_easy_setopt(curl, CURLOPT_SSLENGINE_DEFAULT, 1);
-
-      /* where to store */
-      curl_easy_setopt(curl, CURLOPT_WRITEDATA, (FILE *)&outs);
-      /* what call to write */
-      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
-
-      /* for uploads */
-      input.stream = infd;
-      input.config = config;
-      curl_easy_setopt(curl, CURLOPT_READDATA, &input);
-      /* what call to read */
-      curl_easy_setopt(curl, CURLOPT_READFUNCTION, my_fread);
-
-      if(config->recvpersecond) {
-        /* tell libcurl to use a smaller sized buffer as it allows us to
-           make better sleeps! 7.9.9 stuff! */
-        curl_easy_setopt(curl, CURLOPT_BUFFERSIZE, config->recvpersecond);
-      }
-
-      /* size of uploaded file: */
-      curl_easy_setopt(curl, CURLOPT_INFILESIZE, infilesize);
-      curl_easy_setopt(curl, CURLOPT_URL, url);     /* what to fetch */
-      curl_easy_setopt(curl, CURLOPT_PROXY, config->proxy); /* proxy to use */
-      curl_easy_setopt(curl, CURLOPT_HEADER, config->conf&CONF_HEADER);
-      curl_easy_setopt(curl, CURLOPT_NOPROGRESS, config->conf&CONF_NOPROGRESS);
-      curl_easy_setopt(curl, CURLOPT_NOBODY, config->conf&CONF_NOBODY);
-      curl_easy_setopt(curl, CURLOPT_FAILONERROR,
-                       config->conf&CONF_FAILONERROR);
-      curl_easy_setopt(curl, CURLOPT_UPLOAD, config->conf&CONF_UPLOAD);
-      curl_easy_setopt(curl, CURLOPT_FTPLISTONLY,
-                       config->conf&CONF_FTPLISTONLY);
-      curl_easy_setopt(curl, CURLOPT_FTPAPPEND, config->conf&CONF_FTPAPPEND);
-
-      if (config->conf&CONF_NETRC_OPT)
-        curl_easy_setopt(curl, CURLOPT_NETRC, CURL_NETRC_OPTIONAL);
-      else if (config->conf&CONF_NETRC)
-        curl_easy_setopt(curl, CURLOPT_NETRC, CURL_NETRC_REQUIRED);
-      else
-        curl_easy_setopt(curl, CURLOPT_NETRC, CURL_NETRC_IGNORED);
+        curl_easy_setopt(curl, CURLOPT_SSLENGINE, config->engine);
+        curl_easy_setopt(curl, CURLOPT_SSLENGINE_DEFAULT, 1);
+
+        /* where to store */
+        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (FILE *)&outs);
+        /* what call to write */
+        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
+
+        /* for uploads */
+        input.stream = infd;
+        input.config = config;
+        curl_easy_setopt(curl, CURLOPT_READDATA, &input);
+        /* what call to read */
+        curl_easy_setopt(curl, CURLOPT_READFUNCTION, my_fread);
+
+        if(config->recvpersecond) {
+          /* tell libcurl to use a smaller sized buffer as it allows us to
+             make better sleeps! 7.9.9 stuff! */
+          curl_easy_setopt(curl, CURLOPT_BUFFERSIZE, config->recvpersecond);
+        }
+
+        /* size of uploaded file: */
+        curl_easy_setopt(curl, CURLOPT_INFILESIZE, uploadfilesize);
+        curl_easy_setopt(curl, CURLOPT_URL, url);     /* what to fetch */
+        curl_easy_setopt(curl, CURLOPT_PROXY, config->proxy); /* proxy to use */
+        curl_easy_setopt(curl, CURLOPT_HEADER, config->conf&CONF_HEADER);
+        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, config->conf&CONF_NOPROGRESS);
+        curl_easy_setopt(curl, CURLOPT_NOBODY, config->conf&CONF_NOBODY);
+        curl_easy_setopt(curl, CURLOPT_FAILONERROR,
+                         config->conf&CONF_FAILONERROR);
+        curl_easy_setopt(curl, CURLOPT_UPLOAD, uploadfile?TRUE:FALSE);
+        curl_easy_setopt(curl, CURLOPT_FTPLISTONLY,
+                         config->conf&CONF_FTPLISTONLY);
+        curl_easy_setopt(curl, CURLOPT_FTPAPPEND, config->conf&CONF_FTPAPPEND);
+
+        if (config->conf&CONF_NETRC_OPT)
+          curl_easy_setopt(curl, CURLOPT_NETRC, CURL_NETRC_OPTIONAL);
+        else if (config->conf&CONF_NETRC)
+          curl_easy_setopt(curl, CURLOPT_NETRC, CURL_NETRC_REQUIRED);
+        else
+          curl_easy_setopt(curl, CURLOPT_NETRC, CURL_NETRC_IGNORED);
 
-      curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION,
-                       config->conf&CONF_FOLLOWLOCATION);
-      curl_easy_setopt(curl, CURLOPT_UNRESTRICTED_AUTH,
-                       config->conf&CONF_UNRESTRICTED_AUTH);
-      curl_easy_setopt(curl, CURLOPT_TRANSFERTEXT, config->conf&CONF_GETTEXT);
-      curl_easy_setopt(curl, CURLOPT_MUTE, config->conf&CONF_MUTE);
-      curl_easy_setopt(curl, CURLOPT_USERPWD, config->userpwd);
-      curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, config->proxyuserpwd);
-      curl_easy_setopt(curl, CURLOPT_RANGE, config->range);
-      curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorbuffer);
-      curl_easy_setopt(curl, CURLOPT_TIMEOUT, config->timeout);
-      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, config->postfields);
+        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION,
+                         config->conf&CONF_FOLLOWLOCATION);
+        curl_easy_setopt(curl, CURLOPT_UNRESTRICTED_AUTH,
+                         config->conf&CONF_UNRESTRICTED_AUTH);
+        curl_easy_setopt(curl, CURLOPT_TRANSFERTEXT, config->conf&CONF_GETTEXT);
+        curl_easy_setopt(curl, CURLOPT_MUTE, config->conf&CONF_MUTE);
+        curl_easy_setopt(curl, CURLOPT_USERPWD, config->userpwd);
+        curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, config->proxyuserpwd);
+        curl_easy_setopt(curl, CURLOPT_RANGE, config->range);
+        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorbuffer);
+        curl_easy_setopt(curl, CURLOPT_TIMEOUT, config->timeout);
+        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, config->postfields);
 
-      /* new in libcurl 7.2: */
-      curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, config->postfieldsize);
+        /* new in libcurl 7.2: */
+        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, config->postfieldsize);
         
-      curl_easy_setopt(curl, CURLOPT_REFERER, config->referer);
-      curl_easy_setopt(curl, CURLOPT_AUTOREFERER,
-                       config->conf&CONF_AUTO_REFERER);
-      curl_easy_setopt(curl, CURLOPT_USERAGENT, config->useragent);
-      curl_easy_setopt(curl, CURLOPT_FTPPORT, config->ftpport);
-      curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, config->low_speed_limit);
-      curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, config->low_speed_time);
-      curl_easy_setopt(curl, CURLOPT_RESUME_FROM,
-                       config->use_resume?config->resume_from:0);
-      curl_easy_setopt(curl, CURLOPT_COOKIE, config->cookie);
-      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, config->headers);
-      curl_easy_setopt(curl, CURLOPT_HTTPPOST, config->httppost);
-      curl_easy_setopt(curl, CURLOPT_SSLCERT, config->cert);
-      curl_easy_setopt(curl, CURLOPT_SSLCERTTYPE, config->cert_type);
-      curl_easy_setopt(curl, CURLOPT_SSLKEY, config->key);
-      curl_easy_setopt(curl, CURLOPT_SSLKEYTYPE, config->key_type);
-      curl_easy_setopt(curl, CURLOPT_SSLKEYPASSWD, config->key_passwd);
-
-      /* default to strict verifyhost */
-      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2);
-      if(config->cacert || config->capath) {
-        if (config->cacert)
-          curl_easy_setopt(curl, CURLOPT_CAINFO, config->cacert);
-
-        if (config->capath)
-          curl_easy_setopt(curl, CURLOPT_CAPATH, config->capath);
-        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, TRUE);
-      }
-      else
+        curl_easy_setopt(curl, CURLOPT_REFERER, config->referer);
+        curl_easy_setopt(curl, CURLOPT_AUTOREFERER,
+                         config->conf&CONF_AUTO_REFERER);
+        curl_easy_setopt(curl, CURLOPT_USERAGENT, config->useragent);
+        curl_easy_setopt(curl, CURLOPT_FTPPORT, config->ftpport);
+        curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, config->low_speed_limit);
+        curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, config->low_speed_time);
+        curl_easy_setopt(curl, CURLOPT_RESUME_FROM,
+                         config->use_resume?config->resume_from:0);
+        curl_easy_setopt(curl, CURLOPT_COOKIE, config->cookie);
+        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, config->headers);
+        curl_easy_setopt(curl, CURLOPT_HTTPPOST, config->httppost);
+        curl_easy_setopt(curl, CURLOPT_SSLCERT, config->cert);
+        curl_easy_setopt(curl, CURLOPT_SSLCERTTYPE, config->cert_type);
+        curl_easy_setopt(curl, CURLOPT_SSLKEY, config->key);
+        curl_easy_setopt(curl, CURLOPT_SSLKEYTYPE, config->key_type);
+        curl_easy_setopt(curl, CURLOPT_SSLKEYPASSWD, config->key_passwd);
+
+        /* default to strict verifyhost */
+        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2);
+        if(config->cacert || config->capath) {
+          if (config->cacert)
+            curl_easy_setopt(curl, CURLOPT_CAINFO, config->cacert);
+
+          if (config->capath)
+            curl_easy_setopt(curl, CURLOPT_CAPATH, config->capath);
+          curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, TRUE);
+        }
         if(config->insecure_ok) {
           /* new stuff needed for libcurl 7.10 */
           curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
           curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1);
         }
       
-      if((config->conf&CONF_NOBODY) ||
-         config->remote_time) {
-        /* no body or use remote time */
-        curl_easy_setopt(curl, CURLOPT_FILETIME, TRUE);
-      }
+        if((config->conf&CONF_NOBODY) ||
+           config->remote_time) {
+          /* no body or use remote time */
+          curl_easy_setopt(curl, CURLOPT_FILETIME, TRUE);
+        }
       
-      if (config->maxredirs) 
-        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, config->maxredirs); 
-      else 
-        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, DEFAULT_MAXREDIRS); 
+        if (config->maxredirs) 
+          curl_easy_setopt(curl, CURLOPT_MAXREDIRS, config->maxredirs); 
+        else 
+          curl_easy_setopt(curl, CURLOPT_MAXREDIRS, DEFAULT_MAXREDIRS); 
  
-      curl_easy_setopt(curl, CURLOPT_CRLF, config->crlf);
-      curl_easy_setopt(curl, CURLOPT_QUOTE, config->quote);
-      curl_easy_setopt(curl, CURLOPT_POSTQUOTE, config->postquote);
-      curl_easy_setopt(curl, CURLOPT_WRITEHEADER,
-                       config->headerfile?&heads:NULL);
-      curl_easy_setopt(curl, CURLOPT_COOKIEFILE, config->cookiefile);
-      /* cookie jar was added in 7.9 */
-      curl_easy_setopt(curl, CURLOPT_COOKIEJAR, config->cookiejar);
-      /* cookie session added in 7.9.7 */
-      curl_easy_setopt(curl, CURLOPT_COOKIESESSION, config->cookiesession);
-
-      curl_easy_setopt(curl, CURLOPT_SSLVERSION, config->ssl_version);
-      curl_easy_setopt(curl, CURLOPT_TIMECONDITION, config->timecond);
-      curl_easy_setopt(curl, CURLOPT_TIMEVALUE, config->condtime);
-      curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, config->customrequest);
-      curl_easy_setopt(curl, CURLOPT_STDERR, config->errors);
+        curl_easy_setopt(curl, CURLOPT_CRLF, config->crlf);
+        curl_easy_setopt(curl, CURLOPT_QUOTE, config->quote);
+        curl_easy_setopt(curl, CURLOPT_POSTQUOTE, config->postquote);
+        curl_easy_setopt(curl, CURLOPT_WRITEHEADER,
+                         config->headerfile?&heads:NULL);
+        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, config->cookiefile);
+        /* cookie jar was added in 7.9 */
+        if(config->cookiejar)
+          curl_easy_setopt(curl, CURLOPT_COOKIEJAR, config->cookiejar);
+        /* cookie session added in 7.9.7 */
+        curl_easy_setopt(curl, CURLOPT_COOKIESESSION, config->cookiesession);
+
+        curl_easy_setopt(curl, CURLOPT_SSLVERSION, config->ssl_version);
+        curl_easy_setopt(curl, CURLOPT_TIMECONDITION, config->timecond);
+        curl_easy_setopt(curl, CURLOPT_TIMEVALUE, config->condtime);
+        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, config->customrequest);
+        curl_easy_setopt(curl, CURLOPT_STDERR, config->errors);
       
-      /* three new ones in libcurl 7.3: */
-      curl_easy_setopt(curl, CURLOPT_HTTPPROXYTUNNEL, config->proxytunnel);
-      curl_easy_setopt(curl, CURLOPT_INTERFACE, config->iface);
-      curl_easy_setopt(curl, CURLOPT_KRB4LEVEL, config->krb4level);
+        /* three new ones in libcurl 7.3: */
+        curl_easy_setopt(curl, CURLOPT_HTTPPROXYTUNNEL, config->proxytunnel);
+        curl_easy_setopt(curl, CURLOPT_INTERFACE, config->iface);
+        curl_easy_setopt(curl, CURLOPT_KRB4LEVEL, config->krb4level);
       
-      if((config->progressmode == CURL_PROGRESS_BAR) &&
-         !(config->conf&(CONF_NOPROGRESS|CONF_MUTE))) {
-        /* we want the alternative style, then we have to implement it
-           ourselves! */
-        progressbarinit(&progressbar, config);
-        curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, myprogress);
-        curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, &progressbar);
-      }
+        if((config->progressmode == CURL_PROGRESS_BAR) &&
+           !(config->conf&(CONF_NOPROGRESS|CONF_MUTE))) {
+          /* we want the alternative style, then we have to implement it
+             ourselves! */
+          progressbarinit(&progressbar, config);
+          curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, myprogress);
+          curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, &progressbar);
+        }
         
-      /* new in libcurl 7.6.2: */
-      curl_easy_setopt(curl, CURLOPT_TELNETOPTIONS, config->telnet_options);
+        /* new in libcurl 7.6.2: */
+        curl_easy_setopt(curl, CURLOPT_TELNETOPTIONS, config->telnet_options);
 
-      /* new in libcurl 7.7: */
-      curl_easy_setopt(curl, CURLOPT_RANDOM_FILE, config->random_file);
-      curl_easy_setopt(curl, CURLOPT_EGDSOCKET, config->egd_file);
-      curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, config->connecttimeout);
-
-      if(config->cipher_list)
-        curl_easy_setopt(curl, CURLOPT_SSL_CIPHER_LIST, config->cipher_list);
-
-      if(config->httpversion)
-        curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, config->httpversion);
-
-      /* new in libcurl 7.9.2: */
-      if(config->disable_epsv)
-        /* disable it */
-        curl_easy_setopt(curl, CURLOPT_FTP_USE_EPSV, FALSE);
-
-      /* new in curl 7.9.7 */
-      if(config->trace_dump) {
-        curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, my_trace);
-        curl_easy_setopt(curl, CURLOPT_DEBUGDATA, config);
-        config->conf |= CONF_VERBOSE; /* force verbose */
-      }
-      curl_easy_setopt(curl, CURLOPT_VERBOSE, config->conf&CONF_VERBOSE);
-
-      /* new in curl 7.10 */
-      curl_easy_setopt(curl, CURLOPT_ENCODING, 
-                       (config->encoding) ? "deflate" : NULL);
+        /* new in libcurl 7.7: */
+        curl_easy_setopt(curl, CURLOPT_RANDOM_FILE, config->random_file);
+        curl_easy_setopt(curl, CURLOPT_EGDSOCKET, config->egd_file);
+        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, config->connecttimeout);
+
+        if(config->cipher_list)
+          curl_easy_setopt(curl, CURLOPT_SSL_CIPHER_LIST, config->cipher_list);
+
+        if(config->httpversion)
+          curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, config->httpversion);
+
+        /* new in libcurl 7.9.2: */
+        if(config->disable_epsv)
+          /* disable it */
+          curl_easy_setopt(curl, CURLOPT_FTP_USE_EPSV, FALSE);
+
+        /* new in libcurl 7.10.5 */
+        if(config->disable_eprt)
+          /* disable it */
+          curl_easy_setopt(curl, CURLOPT_FTP_USE_EPRT, FALSE);
+
+        /* new in libcurl 7.10.6 (default is Basic) */
+        if(config->authtype)
+          curl_easy_setopt(curl, CURLOPT_HTTPAUTH, config->authtype);
+      
+        /* new in curl 7.9.7 */
+        if(config->trace_dump) {
+          curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, my_trace);
+          curl_easy_setopt(curl, CURLOPT_DEBUGDATA, config);
+          config->conf |= CONF_VERBOSE; /* force verbose */
+        }
+        curl_easy_setopt(curl, CURLOPT_VERBOSE, config->conf&CONF_VERBOSE);
+
+        /* new in curl 7.10 */
+        curl_easy_setopt(curl, CURLOPT_ENCODING, 
+                         (config->encoding) ? "" : NULL);
+
+        /* new in curl 7.10.7 */
+        curl_easy_setopt(curl, CURLOPT_FTP_CREATE_MISSING_DIRS,
+                         config->ftp_create_dirs);
+        if(config->proxyntlm)
+          curl_easy_setopt(curl, CURLOPT_PROXYAUTH, CURLAUTH_NTLM);
+
+        /* new in curl 7.10.8 */
+        if (config->max_filesize)
+          curl_easy_setopt(curl, CURLOPT_MAXFILESIZE, config->max_filesize);
 
-      res = curl_easy_perform(curl);
+        res = curl_easy_perform(curl);
         
-      if((config->progressmode == CURL_PROGRESS_BAR) &&
-         progressbar.calls) {
-        /* if the custom progress bar has been displayed, we output a
-           newline here */
-        fputs("\n", progressbar.out);
-      }
+        if((config->progressmode == CURL_PROGRESS_BAR) &&
+           progressbar.calls) {
+          /* if the custom progress bar has been displayed, we output a
+             newline here */
+          fputs("\n", progressbar.out);
+        }
 
-      if(config->writeout) {
-        ourWriteOut(curl, config->writeout);
-      }
+        if(config->writeout) {
+          ourWriteOut(curl, config->writeout);
+        }
 #ifdef USE_ENVIRONMENT
-      if (config->writeenv)
-        ourWriteEnv(curl);
+        if (config->writeenv)
+          ourWriteEnv(curl);
 #endif
 
 #ifdef	VMS
-      if (!config->showerror)  {
-        vms_show = VMSSTS_HIDE;
-      }
+        if (!config->showerror)  {
+          vms_show = VMSSTS_HIDE;
+        }
 #else
-      if((res!=CURLE_OK) && config->showerror)
-        fprintf(config->errors, "curl: (%d) %s\n", res, errorbuffer);
+        if((res!=CURLE_OK) && config->showerror) {
+          if(CURLE_SSL_CACERT == res) {
+            fprintf(config->errors, "curl: (%d) %s\n\n", res, errorbuffer);
+#define CURL_CA_CERT_ERRORMSG1 \
+"More details here: http://curl.haxx.se/docs/sslcerts.html\n\n" \
+"curl performs SSL certificate verification by default, using a \"bundle\"\n" \
+" of Certificate Authority (CA) public keys (CA certs). The default\n" \
+" bundle is named curl-ca-bundle.crt; you can specify an alternate file\n" \
+" using the --cacert option.\n"
+
+#define CURL_CA_CERT_ERRORMSG2 \
+"If this HTTPS server uses a certificate signed by a CA represented in\n" \
+" the bundle, the certificate verification probably failed due to a\n" \
+" problem with the certificate (it might be expired, or the name might\n" \
+" not match the domain name in the URL).\n" \
+"If you'd like to turn off curl's verification of the certificate, use\n" \
+" the -k (or --insecure) option.\n"
+
+            fprintf(config->errors, "%s%s",
+                    CURL_CA_CERT_ERRORMSG1,
+                    CURL_CA_CERT_ERRORMSG2 );
+          }
+          else
+            fprintf(config->errors, "curl: (%d) %s\n", res, errorbuffer);
+        }
 #endif
 
-      if (outfile && !curl_strequal(outfile, "-") && outs.stream)
-        fclose(outs.stream);
+        if (outfile && !curl_strequal(outfile, "-") && outs.stream)
+          fclose(outs.stream);
 
 #ifdef HAVE_UTIME
-      /* Important that we set the time _after_ the file has been 
-         closed, as is done above here */
-      if(config->remote_time && outs.filename) {
-        /* as libcurl if we got a time. Pretty please */
-        long filetime;
-        curl_easy_getinfo(curl, CURLINFO_FILETIME, &filetime);
-        if(filetime >= 0) {
-          struct utimbuf times;
-          times.actime = filetime;
-          times.modtime = filetime;
-          utime(outs.filename, &times); /* set the time we got */
+        /* Important that we set the time _after_ the file has been 
+           closed, as is done above here */
+        if(config->remote_time && outs.filename) {
+          /* as libcurl if we got a time. Pretty please */
+          long filetime;
+          curl_easy_getinfo(curl, CURLINFO_FILETIME, &filetime);
+          if(filetime >= 0) {
+            struct utimbuf times;
+            times.actime = filetime;
+            times.modtime = filetime;
+            utime(outs.filename, &times); /* set the time we got */
+          }
         }
-      }
 #endif
 
-      if (config->infile)
-        fclose(infd);
-      if(headerfilep)
-        fclose(headerfilep);
+        if(headerfilep)
+          fclose(headerfilep);
       
-      if (httpgetfields)
-        free(httpgetfields);
+        if (httpgetfields)
+          free(httpgetfields);
 
-      if(url)
-        free(url);
+        if(url)
+          free(url);
+
+        if(outfile)
+          free(outfile);
+
+        if(infdfopen)
+          fclose(infd);
+
+      } /* loop to the next URL */
+
+      if(urls)
+        /* cleanup memory used for URL globbing patterns */
+        glob_cleanup(urls);
+     
+      if(uploadfile)
+        free(uploadfile);
+ 
+    } /* loop to the next globbed upload file */
+
+    if(inglob)
+      glob_cleanup(inglob);
 
-      if(outfile)
-        free(outfile);
-    }
     if(outfiles)
       free(outfiles);
 
-    if(urls)
-      /* cleanup memory used for URL globbing patterns */
-      glob_cleanup(urls);
-
     /* empty this urlnode struct */
     if(urlnode->url)
       free(urlnode->url);
     if(urlnode->outfile)
       free(urlnode->outfile);
+    if(urlnode->infile)
+      free(urlnode->infile);
     
     /* move on to the next URL */
     nextnode=urlnode->next;
     free(urlnode); /* free the node */
     urlnode = nextnode;
 
