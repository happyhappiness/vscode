(opMode == OM_UNZ) {
      unzFailsExist = False;
      if (srcMode == SM_I2O) {
         uncompress ( NULL );
      } else {
         decode = True;
         for (aa = argList; aa != NULL; aa = aa->link) {
            if (ISFLAG("--")) { decode = False; continue; }
            if (aa->name[0] == '-' && decode) continue;
            numFilesProcessed++;
            uncompress ( aa->name );
         }      
      }
      if (unzFailsExist) { 
         setExit(2); 
         exit(exitValue);
      }
   }