 
 /* Save the history in the specified file. On success 0 is returned
  * otherwise -1 is returned. */
 int linenoiseHistorySave(const char *filename) {
     FILE *fp = fopen(filename,"w");
     int j;
-    
+
     if (fp == NULL) return -1;
     for (j = 0; j < history_len; j++)
         fprintf(fp,"%s\n",history[j]);
     fclose(fp);
     return 0;
 }
