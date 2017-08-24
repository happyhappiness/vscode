{
      case SM_I2O: 
         copyFileName ( inName, (Char*)"(stdin)" );
         copyFileName ( outName, (Char*)"(stdout)" ); 
         break;
      case SM_F2F: 
         copyFileName ( inName, name );
         copyFileName ( outName, name );
         for (i = 0; i < BZ_N_SUFFIX_PAIRS; i++)
            if (mapSuffix(outName,zSuffix[i],unzSuffix[i]))
               goto zzz; 
         cantGuess = True;
         strcat ( outName, ".out" );
         break;
      case SM_F2O: 
         copyFileName ( inName, name );
         copyFileName ( outName, (Char*)"(stdout)" ); 
         break;
   }