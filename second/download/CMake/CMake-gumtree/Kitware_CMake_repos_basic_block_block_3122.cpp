{
         if (myfeof(zStream)) break;
         nread = fread ( obuf, sizeof(UChar), 5000, zStream );
         if (ferror(zStream)) goto errhandler_io;
         if (nread > 0) fwrite ( obuf, sizeof(UChar), nread, stream );
         if (ferror(stream)) goto errhandler_io;
      }