int dprintf_Pass1Report(va_stack_t *vto, int max)
{
  int i;
  char buffer[128];
  int bit;
  int flags;

  for(i=0; i<max; i++) {
    char *type;
    switch(vto[i].type) {
    case FORMAT_UNKNOWN:
      type = "unknown";
      break;
    case FORMAT_STRING:
      type ="string";
      break;
    case FORMAT_PTR:
      type ="pointer";
      break;
    case FORMAT_INT:
      type = "int";
      break;
    case FORMAT_LONG:
      type = "long";
      break;
    case FORMAT_LONGLONG:
      type = "long long";
      break;
    case FORMAT_DOUBLE:
      type = "double";
      break;
    case FORMAT_LONGDOUBLE:
      type = "long double";
      break;      
    }


    buffer[0]=0;

    for(bit=0; bit<31; bit++) {
      flags = vto[i].flags & (1<<bit);

      if(flags & FLAGS_SPACE)
	strcat(buffer, "space ");
      else if(flags & FLAGS_SHOWSIGN)
	strcat(buffer, "plus ");
      else if(flags & FLAGS_LEFT)
	strcat(buffer, "left ");
      else if(flags & FLAGS_ALT)
	strcat(buffer, "alt ");
      else if(flags & FLAGS_SHORT)
	strcat(buffer, "short ");
      else if(flags & FLAGS_LONG)
	strcat(buffer, "long ");
      else if(flags & FLAGS_LONGLONG)
	strcat(buffer, "longlong ");
      else if(flags & FLAGS_LONGDOUBLE)
	strcat(buffer, "longdouble ");
      else if(flags & FLAGS_PAD_NIL)
	strcat(buffer, "padnil ");
      else if(flags & FLAGS_UNSIGNED)
	strcat(buffer, "unsigned ");
      else if(flags & FLAGS_OCTAL)
	strcat(buffer, "octal ");
      else if(flags & FLAGS_HEX)
	strcat(buffer, "hex ");
      else if(flags & FLAGS_UPPER)
	strcat(buffer, "upper ");
      else if(flags & FLAGS_WIDTH)
	strcat(buffer, "width ");
      else if(flags & FLAGS_WIDTHPARAM)
	strcat(buffer, "widthparam ");
      else if(flags & FLAGS_PREC)
	strcat(buffer, "precision ");
      else if(flags & FLAGS_PRECPARAM)
	strcat(buffer, "precparam ");
      else if(flags & FLAGS_CHAR)
	strcat(buffer, "char ");
      else if(flags & FLAGS_FLOATE)
	strcat(buffer, "floate ");
      else if(flags & FLAGS_FLOATG)
	strcat(buffer, "floatg ");
    }
    printf("REPORT: %d. %s [%s]\n", i, type, buffer);

  }


}