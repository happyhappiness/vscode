{
          temp = (buffer == NULL
                ? (char *)MALLOC(bytesToAllocate)
                : (char *)REALLOC(buffer, bytesToAllocate));
        }