    }

  else

    {

#if defined( CM_GLOB_CASE_INDEPENDENT )

    // On Windows and apple, no difference between lower and upper case

    sprintf(buffer, "%c", tolower(ch));

#else

