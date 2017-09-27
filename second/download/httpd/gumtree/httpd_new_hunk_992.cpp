        }
      else options = handle_option(*s++, options);
      }
    }
  }

pattern_list = (pcre **)malloc(MAX_PATTERN_COUNT * sizeof(pcre *));
hints_list = (pcre_extra **)malloc(MAX_PATTERN_COUNT * sizeof(pcre_extra *));

if (pattern_list == NULL || hints_list == NULL)
  {
  fprintf(stderr, "pcregrep: malloc failed\n");
  return 2;
  }
