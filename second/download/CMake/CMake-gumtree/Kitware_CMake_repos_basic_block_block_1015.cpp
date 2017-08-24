{
      // A '?' (not between brackets) matches any single character.
      // We modify this to not match slashes since the orignal glob
      // pattern documentation was meant for matching file name
      // components separated by slashes.
      regex += "[^/]";
    }