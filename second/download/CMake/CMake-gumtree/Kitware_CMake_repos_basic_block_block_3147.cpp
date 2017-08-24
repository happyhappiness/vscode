{
      case BZ_CONFIG_ERROR:
         configError(); break;
      case BZ_IO_ERROR:
         errhandler_io:
         ioError(); break;
      case BZ_DATA_ERROR:
         fprintf ( stderr,
                   "data integrity (CRC) error in data\n" );
         return False;
      case BZ_MEM_ERROR:
         outOfMemory();
      case BZ_UNEXPECTED_EOF:
         fprintf ( stderr,
                   "file ends unexpectedly\n" );
         return False;
      case BZ_DATA_ERROR_MAGIC:
         if (zStream != stdin) fclose(zStream);
         if (streamNo == 1) {
          fprintf ( stderr, 
                    "bad magic number (file not created by bzip2)\n" );
            return False;
         } else {
            if (noisy)
            fprintf ( stderr, 
                      "trailing garbage after EOF ignored\n" );
            return True;       
         }
      default:
         panic ( "test:unexpected error" );
   }