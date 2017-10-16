       config->content_disposition = toggle;
       break;
     case 'k': /* allow insecure SSL connects */
       config->insecure_ok = toggle;
       break;
     case 'K': /* parse config file */
-      if(parseconfig(nextarg, config))
+      if(parseconfig(nextarg, global))
         warnf(config, "error trying read config from the '%s' file\n",
               nextarg);
       break;
     case 'l':
       config->dirlistonly = toggle; /* only list the names of the FTP dir */
       break;
