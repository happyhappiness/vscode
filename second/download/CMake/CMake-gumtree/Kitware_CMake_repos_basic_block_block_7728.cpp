{
      const XML_Char *s = appAtts[i];
      if (s[-1] == 2) {  /* prefixed */
        ATTRIBUTE_ID *id;
        const BINDING *b;
        unsigned long uriHash;
        struct siphash sip_state;
        struct sipkey sip_key;

        copy_salt_to_sipkey(parser, &sip_key);
        sip24_init(&sip_state, &sip_key);

        ((XML_Char *)s)[-1] = 0;  /* clear flag */
        id = (ATTRIBUTE_ID *)lookup(parser, &dtd->attributeIds, s, 0);
        if (!id || !id->prefix)
          return XML_ERROR_NO_MEMORY;
        b = id->prefix->binding;
        if (!b)
          return XML_ERROR_UNBOUND_PREFIX;

        for (j = 0; j < b->uriLen; j++) {
          const XML_Char c = b->uri[j];
          if (!poolAppendChar(&tempPool, c))
            return XML_ERROR_NO_MEMORY;
        }

        sip24_update(&sip_state, b->uri, b->uriLen * sizeof(XML_Char));

        while (*s++ != XML_T(ASCII_COLON))
          ;

        sip24_update(&sip_state, s, keylen(s) * sizeof(XML_Char));

        do {  /* copies null terminator */
          if (!poolAppendChar(&tempPool, *s))
            return XML_ERROR_NO_MEMORY;
        } while (*s++);

        uriHash = (unsigned long)sip24_final(&sip_state);

        { /* Check hash table for duplicate of expanded name (uriName).
             Derived from code in lookup(parser, HASH_TABLE *table, ...).
          */
          unsigned char step = 0;
          unsigned long mask = nsAttsSize - 1;
          j = uriHash & mask;  /* index into hash table */
          while (nsAtts[j].version == version) {
            /* for speed we compare stored hash values first */
            if (uriHash == nsAtts[j].hash) {
              const XML_Char *s1 = poolStart(&tempPool);
              const XML_Char *s2 = nsAtts[j].uriName;
              /* s1 is null terminated, but not s2 */
              for (; *s1 == *s2 && *s1 != 0; s1++, s2++);
              if (*s1 == 0)
                return XML_ERROR_DUPLICATE_ATTRIBUTE;
            }
            if (!step)
              step = PROBE_STEP(uriHash, mask, nsAttsPower);
            j < step ? (j += nsAttsSize - step) : (j -= step);
          }
        }

        if (ns_triplets) {  /* append namespace separator and prefix */
          tempPool.ptr[-1] = namespaceSeparator;
          s = b->prefix->name;
          do {
            if (!poolAppendChar(&tempPool, *s))
              return XML_ERROR_NO_MEMORY;
          } while (*s++);
        }

        /* store expanded name in attribute list */
        s = poolStart(&tempPool);
        poolFinish(&tempPool);
        appAtts[i] = s;

        /* fill empty slot with new version, uriName and hash value */
        nsAtts[j].version = version;
        nsAtts[j].hash = uriHash;
        nsAtts[j].uriName = s;

        if (!--nPrefixes) {
          i += 2;
          break;
        }
      }
      else  /* not prefixed */
        ((XML_Char *)s)[-1] = 0;  /* clear flag */
    }