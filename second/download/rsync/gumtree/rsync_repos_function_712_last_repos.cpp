static LDOUBLE POW10(int exp)
{
	LDOUBLE result = 1;
	
	while (exp) {
		result *= 10;
		exp--;
	}
  
	return result;
}