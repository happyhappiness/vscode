      newlen += 2; /* the size grows with two, since this'll become a %XX */
      if(newlen > alloc) {
        alloc *= 2;
        ns = realloc(ns, alloc);
        if(!ns)
          return NULL;
      }
      sprintf(&ns[index], "%%%02X", in);

