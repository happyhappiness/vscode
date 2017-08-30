    }

  else

    {

#if defined( _WIN32 ) || defined(APPLE)

    // On Windows and apple, no difference between lower and upper case

    sprintf(buffer, "%c", tolower(ch));

#else

    sprintf(buffer, "%c", ch);

#endif

    }

}



