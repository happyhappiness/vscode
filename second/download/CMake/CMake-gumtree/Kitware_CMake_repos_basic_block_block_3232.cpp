( srcMode == SM_F2F && fileExists ( outName ) ) {
      if (forceOverwrite) {
    remove(outName);
      } else {
        fprintf ( stderr, "%s: Output file %s already exists.\n",
                  progName, outName );
        setExit(1);
        return;
      }
   }