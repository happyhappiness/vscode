   if ((certfile = smime_extract_certificate(infile)))
   {
     mutt_endwin (NULL);
   
     if ((thepid =  smime_invoke (&smimein, NULL, NULL,
 				 -1, fileno(fpout), fileno(fperr),
-				 certfile, NULL, NULL, NULL, NULL, NULL,
+				 certfile, NULL, NULL, NULL, NULL, NULL, NULL,
 				 SmimeImportCertCommand))== -1)
     {
       mutt_message (_("Error: unable to create OpenSSL subprocess!"));
       return;
     }
     fputs (buf, smimein);
