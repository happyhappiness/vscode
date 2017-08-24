(oldE->defaultAtts[i].value) {
        newE->defaultAtts[i].value
            = poolCopyString(&(newDtd->pool), oldE->defaultAtts[i].value);
        if (!newE->defaultAtts[i].value)
          return 0;
      }
      else
        newE->defaultAtts[i].value = NULL