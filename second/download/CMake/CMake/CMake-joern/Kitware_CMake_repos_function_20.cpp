Int32 main ( Int32 argc, Char** argv )
{
   FILE*       inFile;
   FILE*       outFile;
   BitStream*  bsIn, *bsWr;
   Int32       b, wrBlock, currBlock, rbCtr;
   MaybeUInt64 bitsRead;

   UInt32      buffHi, buffLo, blockCRC;
   Char*       p;

   strcpy ( progName, argv[0] );
   inFileName[0] = outFileName[0] = 0;

   fprintf ( stderr, 
             "bzip2recover 1.0.5: extracts blocks from damaged .bz2 files.\n" );

   if (argc != 2) {
      fprintf ( stderr, "%s: usage is `%s damaged_file_name'.\n",
                        progName, progName );
      switch (sizeof(MaybeUInt64)) {
         case 8:
            fprintf(stderr, 
                    "\trestrictions on size of recovered file: None\n");
            break;
         case 4:
            fprintf(stderr, 
                    "\trestrictions on size of recovered file: 512 MB\n");
            fprintf(stderr, 
                    "\tto circumvent, recompile with MaybeUInt64 as an\n"
                    "\tunsigned 64-bit int.\n");
            break;
         default:
            fprintf(stderr, 
                    "\tsizeof(MaybeUInt64) is not 4 or 8 -- "
                    "configuration error.\n");
            break;
      }
      exit(1);
   }

   if (strlen(argv[1]) >= BZ_MAX_FILENAME-20) {
      fprintf ( stderr, 
                "%s: supplied filename is suspiciously (>= %d chars) long.  Bye!\n",
                progName, (int)strlen(argv[1]) );
      exit(1);
   }

   strcpy ( inFileName, argv[1] );

   inFile = fopen ( inFileName, "rb" );
   if (inFile == NULL) {
      fprintf ( stderr, "%s: can't read `%s'\n", progName, inFileName );
      exit(1);
   }

   bsIn = bsOpenReadStream ( inFile );
   fprintf ( stderr, "%s: searching for block boundaries ...\n", progName );

   bitsRead = 0;
   buffHi = buffLo = 0;
   currBlock = 0;
   bStart[currBlock] = 0;

   rbCtr = 0;

   while (True) {
      b = bsGetBit ( bsIn );
      bitsRead++;
      if (b == 2) {
         if (bitsRead >= bStart[currBlock] &&
            (bitsRead - bStart[currBlock]) >= 40) {
            bEnd[currBlock] = bitsRead-1;
            if (currBlock > 0)
               fprintf ( stderr, "   block %d runs from " MaybeUInt64_FMT 
                                 " to " MaybeUInt64_FMT " (incomplete)\n",
                         currBlock,  bStart[currBlock], bEnd[currBlock] );
         } else
            currBlock--;
         break;
      }
      buffHi = (buffHi << 1) | (buffLo >> 31);
      buffLo = (buffLo << 1) | (b & 1);
      if ( ( (buffHi & 0x0000ffff) == BLOCK_HEADER_HI 
             && buffLo == BLOCK_HEADER_LO)
           || 
           ( (buffHi & 0x0000ffff) == BLOCK_ENDMARK_HI 
             && buffLo == BLOCK_ENDMARK_LO)
         ) {
         if (bitsRead > 49) {
            bEnd[currBlock] = bitsRead-49;
         } else {
            bEnd[currBlock] = 0;
         }
         if (currBlock > 0 &&
         (bEnd[currBlock] - bStart[currBlock]) >= 130) {
            fprintf ( stderr, "   block %d runs from " MaybeUInt64_FMT 
                              " to " MaybeUInt64_FMT "\n",
                      rbCtr+1,  bStart[currBlock], bEnd[currBlock] );
            rbStart[rbCtr] = bStart[currBlock];
            rbEnd[rbCtr] = bEnd[currBlock];
            rbCtr++;
         }
         if (currBlock >= BZ_MAX_HANDLED_BLOCKS)
            tooManyBlocks(BZ_MAX_HANDLED_BLOCKS);
         currBlock++;

         bStart[currBlock] = bitsRead;
      }
   }

   bsClose ( bsIn );

   /*-- identified blocks run from 1 to rbCtr inclusive. --*/

   if (rbCtr < 1) {
      fprintf ( stderr,
                "%s: sorry, I couldn't find any block boundaries.\n",
                progName );
      exit(1);
   };

   fprintf ( stderr, "%s: splitting into blocks\n", progName );

   inFile = fopen ( inFileName, "rb" );
   if (inFile == NULL) {
      fprintf ( stderr, "%s: can't open `%s'\n", progName, inFileName );
      exit(1);
   }
   bsIn = bsOpenReadStream ( inFile );

   /*-- placate gcc's dataflow analyser --*/
   blockCRC = 0; bsWr = 0;

   bitsRead = 0;
   outFile = NULL;
   wrBlock = 0;
   while (True) {
      b = bsGetBit(bsIn);
      if (b == 2) break;
      buffHi = (buffHi << 1) | (buffLo >> 31);
      buffLo = (buffLo << 1) | (b & 1);
      if (bitsRead == 47+rbStart[wrBlock]) 
         blockCRC = (buffHi << 16) | (buffLo >> 16);

      if (outFile != NULL && bitsRead >= rbStart[wrBlock]
                          && bitsRead <= rbEnd[wrBlock]) {
         bsPutBit ( bsWr, b );
      }

      bitsRead++;

      if (bitsRead == rbEnd[wrBlock]+1) {
         if (outFile != NULL) {
            bsPutUChar ( bsWr, 0x17 ); bsPutUChar ( bsWr, 0x72 );
            bsPutUChar ( bsWr, 0x45 ); bsPutUChar ( bsWr, 0x38 );
            bsPutUChar ( bsWr, 0x50 ); bsPutUChar ( bsWr, 0x90 );
            bsPutUInt32 ( bsWr, blockCRC );
            bsClose ( bsWr );
         }
         if (wrBlock >= rbCtr) break;
         wrBlock++;
      } else
      if (bitsRead == rbStart[wrBlock]) {
         /* Create the output file name, correctly handling leading paths. 
            (31.10.2001 by Sergey E. Kusikov) */
         Char* split;
         Int32 ofs, k;
         for (k = 0; k < BZ_MAX_FILENAME; k++) 
            outFileName[k] = 0;
         strcpy (outFileName, inFileName);
         split = strrchr (outFileName, BZ_SPLIT_SYM);
         if (split == NULL) {
            split = outFileName;
         } else {
            ++split;
     }
     /* Now split points to the start of the basename. */
         ofs  = split - outFileName;
         sprintf (split, "rec%5d", wrBlock+1);
         for (p = split; *p != 0; p++) if (*p == ' ') *p = '0';
         strcat (outFileName, inFileName + ofs);

         if ( !endsInBz2(outFileName)) strcat ( outFileName, ".bz2" );

         fprintf ( stderr, "   writing block %d to `%s' ...\n",
                           wrBlock+1, outFileName );

         outFile = fopen ( outFileName, "wb" );
         if (outFile == NULL) {
            fprintf ( stderr, "%s: can't write `%s'\n",
                      progName, outFileName );
            exit(1);
         }
         bsWr = bsOpenWriteStream ( outFile );
         bsPutUChar ( bsWr, BZ_HDR_B );    
         bsPutUChar ( bsWr, BZ_HDR_Z );    
         bsPutUChar ( bsWr, BZ_HDR_h );    
         bsPutUChar ( bsWr, BZ_HDR_0 + 9 );
         bsPutUChar ( bsWr, 0x31 ); bsPutUChar ( bsWr, 0x41 );
         bsPutUChar ( bsWr, 0x59 ); bsPutUChar ( bsWr, 0x26 );
         bsPutUChar ( bsWr, 0x53 ); bsPutUChar ( bsWr, 0x59 );
      }
   }

   fprintf ( stderr, "%s: finished\n", progName );
   return 0;
}