	}
	globfree(&globbuf);
	(*argc) += i;
#endif
}


/*******************************************************************
  convert a string to lower case
********************************************************************/
void strlower(char *s)
{
	while (*s) {
		if (isupper(*s)) *s = tolower(*s);
		s++;
	}
}
