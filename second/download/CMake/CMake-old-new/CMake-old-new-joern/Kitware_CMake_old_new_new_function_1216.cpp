kwsys_stl::string Glob::PatternToRegex(const kwsys_stl::string& pattern,
                                       bool require_whole_string)
{
  // Incrementally build the regular expression from the pattern.
  kwsys_stl::string regex = require_whole_string? "^" : "";
  kwsys_stl::string::const_iterator pattern_first = pattern.begin();
  kwsys_stl::string::const_iterator pattern_last = pattern.end();
  for(kwsys_stl::string::const_iterator i = pattern_first;
      i != pattern_last; ++i)
    {
    int c = *i;
    if(c == '*')
      {
      // A '*' (not between brackets) matches any string.
      regex += ".*";
      }
    else if(c == '?')
      {
      // A '?' (not between brackets) matches any single character.
      regex += ".";
      }
    else if(c == '[')
      {
      // Parse out the bracket expression.  It begins just after the
      // opening character.
      kwsys_stl::string::const_iterator bracket_first = i+1;
      kwsys_stl::string::const_iterator bracket_last = bracket_first;

      // The first character may be complementation '!' or '^'.
      if(bracket_last != pattern_last &&
         (*bracket_last == '!' || *bracket_last == '^'))
        {
        ++bracket_last;
        }

      // If the next character is a ']' it is included in the brackets
      // because the bracket string may not be empty.
      if(bracket_last != pattern_last && *bracket_last == ']')
        {
        ++bracket_last;
        }

      // Search for the closing ']'.
      while(bracket_last != pattern_last && *bracket_last != ']')
        {
        ++bracket_last;
        }

      // Check whether we have a complete bracket string.
      if(bracket_last == pattern_last)
        {
        // The bracket string did not end, so it was opened simply by
        // a '[' that is supposed to be matched literally.
        regex += "\\[";
        }
      else
        {
        // Convert the bracket string to its regex equivalent.
        kwsys_stl::string::const_iterator k = bracket_first;

        // Open the regex block.
        regex += "[";

        // A regex range complement uses '^' instead of '!'.
        if(k != bracket_last && *k == '!')
          {
          regex += "^";
          ++k;
          }

        // Convert the remaining characters.
        for(; k != bracket_last; ++k)
          {
          // Backslashes must be escaped.
          if(*k == '\\')
            {
            regex += "\\";
            }

          // Store this character.
          regex += *k;
          }

        // Close the regex block.
        regex += "]";

        // Jump to the end of the bracket string.
        i = bracket_last;
        }
      }
    else
      {
      // A single character matches itself.
      int ch = c;
      if(!(('a' <= ch && ch <= 'z') ||
           ('A' <= ch && ch <= 'Z') ||
           ('0' <= ch && ch <= '9')))
        {
        // Escape the non-alphanumeric character.
        regex += "\\";
        }
#if defined(KWSYS_GLOB_CASE_INDEPENDENT)
      else
        {
        // On case-insensitive systems file names are converted to lower
        // case before matching.
        ch = tolower(ch);
        }
#endif

      // Store the character.
      regex.append(1, static_cast<char>(ch));
      }
    }

  if(require_whole_string)
    {
    regex += "$";
    }
  return regex;
}