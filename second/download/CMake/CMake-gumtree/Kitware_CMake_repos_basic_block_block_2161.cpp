(fin) {
      fin.read(buffer, bufferSize);
      if (fin.gcount()) {
        fout.write(buffer, fin.gcount());
      } else {
        break;
      }
    }