(forceOverwrite) {
     remove(outName);
      } else {
     fprintf ( stderr, "%s: Output file %s already exists.\n",
           progName, outName );
     setExit(1);
     return;
      }