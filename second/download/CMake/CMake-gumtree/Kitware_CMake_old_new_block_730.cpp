e((n = (int)fread(buffer, 1, 1024, ifp)) > 0)
    {
    fprintf(ofp, "static unsigned char kwsysEncodedArray%s_%d[%d] = {\n", 
            argv[4], count++, n);
    for(i=0; i < n-1; ++i)
      {
      fprintf(ofp, "0x%02X", buffer[i]);
      if(i%10 == 9)
        {
        fprintf(ofp, ",\n");
        }
      else
        {
        fprintf(ofp, ", ");
        }
      }
    fprintf(ofp, "0x%02X};\n\n", buffer[n-1]);
    }