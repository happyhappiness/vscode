             file = stdin;
             set_binmode(stdin);
           }
           else {
             file = fopen(p, "rb");
             if(!file)
-              warnf(config,
+              warnf(global,
                     "Couldn't read data from file \"%s\", this makes "
                     "an empty POST.\n", nextarg);
           }
 
           err = file2memory(&postdata, &size, file);
 
