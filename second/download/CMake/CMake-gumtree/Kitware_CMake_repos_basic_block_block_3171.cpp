{
    fprintf ( stderr,
          "\n%s: Compressed file ends unexpectedly;\n\t"
          "perhaps it is corrupted?  *Possible* reason follows.\n",
          progName );
    perror ( progName );
    showFileNames();
    cadvise();
  }