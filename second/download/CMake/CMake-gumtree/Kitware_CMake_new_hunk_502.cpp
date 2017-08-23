    fprintf(stderr, "\n****\n");
    fprintf(stderr, "**** Header %s\n ", header);
  });

  free(type2);

  return result;
}

/* copy the source to the destination and fill in zeroes in every
   other destination byte! */
static void unicodecpy(unsigned char *dest, const char *src, size_t length)
