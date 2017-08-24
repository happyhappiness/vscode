(strlen(unameInfo.release) >= 3) {
    // release looks like "2.6.3-15mdk-i686-up-4GB"
    char majorChar = unameInfo.release[0];
    char minorChar = unameInfo.release[2];

    if (isdigit(majorChar)) {
      linuxMajor = majorChar - '0';
    }

    if (isdigit(minorChar)) {
      linuxMinor = minorChar - '0';
    }
  }