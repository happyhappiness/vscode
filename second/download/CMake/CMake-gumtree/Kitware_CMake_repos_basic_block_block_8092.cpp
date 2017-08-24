(j = 0; j < i; j++) {
            if (!poolAppendChar(&dtd->pool, name[j]))
              return NULL;
          }