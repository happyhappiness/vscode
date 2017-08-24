( srcMode == SM_F2F ) {
      applySavedTimeInfoToOutputFile ( outName );
      deleteOutputOnInterrupt = False;
      if ( !keepInputFiles ) {
         IntNative retVal = remove ( inName );
         ERROR_IF_NOT_ZERO ( retVal );
      }
   }