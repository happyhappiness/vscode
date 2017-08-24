{
      s = bp;
      while(*bp && isalpha(*bp)) 
	bp++;
      l = (int)(bp-s);
      while(*bp && *bp==' ') 
	bp++;
    }