    case PCRE_ERROR_NOMATCH: printf("No match\n"); break;
    /*
    Handle other special cases if you like
    */
    default: printf("Matching error %d\n", rc); break;
    }
  return 1;
  }

/* Match succeded */

printf("Match succeeded\n");

/* The output vector wasn't big enough */

if (rc == 0)
  {
  rc = OVECCOUNT/3;
  printf("ovector only has room for %d captured substrings\n", rc - 1);
  }

/* Show substrings stored in the output vector */

for (i = 0; i < rc; i++)
  {
  char *substring_start = argv[2] + ovector[2*i];
  int substring_length = ovector[2*i+1] - ovector[2*i];
  printf("%2d: %.*s\n", i, substring_length, substring_start);
  }

return 0;
}


