{
      if (pos > b0 && pos < b1) {
        inQuotes = true;
        break;
      }
      b0 = command.find('"', b1 + 1);
      b1 = command.find('"', b0 + 1);
    }