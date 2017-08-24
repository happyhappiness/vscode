{
        tem = poolCopyString(newPool, oldE->publicId);
        if (!tem)
          return 0;
        newE->publicId = tem;
      }