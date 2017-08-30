      * really checking for IMAGE_FILE_HEADER.Machine == i386 (0x14C)

      * and IMAGE_FILE_HEADER.SizeOfOptionalHeader == 0;

      */

      DumpObjFile((PIMAGE_FILE_HEADER) lpFileBase, fout, full, fort);

   } else {

      printf("unrecognized file format\n");

   }

   UnmapViewOfFile(lpFileBase);

   CloseHandle(hFileMapping);

   CloseHandle(hFile);

}



void

main(int argc, char **argv)

{

   std::string cmdline;

   int i, arg;

   FILE *fout;

   int full = 0;

   int fort = 0;

   char *dllname = "";

   char *outfile = NULL;



   if (argc < 3) {

Usage:

      fprintf(stderr, "Usage: %s ?-o outfile? ?-f(ull)? <dllname> <object filenames> ..\n", argv[0]);

      exit(1);

   }



   arg = 1;

   while (argv[arg][0] == '-') {

      if (strcmp(argv[arg], "--") == 0) {

         arg++;

         break;

      } else if (strcmp(argv[arg], "-f") == 0) {

         full = 1;

      } else if (strcmp(argv[arg], "-x") == 0) {

         fort = 1;

      } else if (strcmp(argv[arg], "-o") == 0) {

         arg++;

         if (arg == argc) {

            goto Usage;

         }

         outfile = argv[arg];

      }

      arg++;

   }

   if (arg == argc) {

      goto Usage;

   }



   if (outfile) {

      fout = fopen(outfile, "w+");

      if (fout == NULL) {

         fprintf(stderr, "Unable to open \'%s\' for writing:\n",

            argv[arg]);

         perror("");

         exit(1);

      }

   } else {

      fout = stdout;

   }



   if (! full) {

      dllname = argv[arg];

      arg++;

      if (arg == argc) {

         goto Usage;

      }

      fprintf(fout, "LIBRARY    %s\n", dllname);

#ifndef _X86_

      fprintf(fout, "CODE PRELOAD MOVEABLE DISCARDABLE\n");

      fprintf(fout, "DATA PRELOAD MOVEABLE MULTIPLE\n\n");

#endif

   }



   for (; arg < argc; arg++) {

      WIN32_FIND_DATA FindFileData;

      HANDLE SearchFile;

      if (argv[arg][0] == '@') {

         std::ifstream fargs(&argv[arg][1]);

         if (!fargs) {

            fprintf(stderr, "Unable to open \'%s\' for reading:\n",

               argv[arg]);

            perror("");

            exit(1);

         }

         char *fargv[1000];

         for (i = 0; i < arg; i++) {

            cmdline += argv[i];

            fargv[i] = argv[i];

         }

         std::string line;

         std::getline(fargs, line);

         cmdline += line;

         fprintf(stderr, "%s\n", line.c_str());

         i += GetArgcArgv(line, &fargv[i]);

         argc = i;

         argv = fargv;

      }

      /*

      *  Argument can contain the wildcard names

      */

      SearchFile = FindFirstFile(argv[arg],&FindFileData);

      if (SearchFile == INVALID_HANDLE_VALUE){

         fprintf(stderr, "Unable to find \'%s\' for reading:\n",

            argv[arg]);

         exit(1);

      }

      else  {

         /*

         *  Since WIN32_FIND_DATA has no path information one has to extract it himself.

         */

         TCHAR *filename = argv[arg];

         TCHAR path[2048];

         size_t i = strlen(filename);

         i--;

         while( filename[i] != '\\' && filename[i] != '/'  && i >=0) i--;

         do

         {

            if (i >= 0) strncpy( path, filename, i+1); /* Generate the 'path' info */

            path[i+1] = '\0';

            DumpFile(strcat(path, FindFileData.cFileName), fout, full, fort);

         } while (FindNextFile(SearchFile,&FindFileData));





         FindClose(SearchFile);

      }

   }

   exit(0);

}
