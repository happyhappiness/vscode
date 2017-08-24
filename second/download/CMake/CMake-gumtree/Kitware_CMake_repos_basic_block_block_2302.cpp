((rpos > lpos) && (data[rpos - 1] == '\r')) {
      // Line ends in a "\r\n" pair, remove both characters.
      lines.push_back(data.substr(lpos, (rpos - 1) - lpos));
    } else {
      // Line ends in a "\n", remove the character.
      lines.push_back(data.substr(lpos, rpos - lpos));
    }