           FILE *file;
 
           nextarg++; /* pass the @ */
 
           if(curlx_strequal("-", nextarg)) {
             file = stdin;
-#ifdef O_BINARY
             if(subletter == 'b') /* forced binary */
-              setmode(fileno(stdin), O_BINARY);
-#endif
+              SET_BINMODE(stdin);
           }
           else {
             file = fopen(nextarg, "rb");
             if(!file)
               warnf(config, "Couldn't read data from file \"%s\", this makes "
                     "an empty POST.\n", nextarg);
