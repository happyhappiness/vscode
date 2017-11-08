char *getpass_r(const char *prompt, char *buffer, size_t buflen)
{
  size_t i = 0;

  printf("%s", prompt);
  do {
    buffer[i++] = getch();
    if(buffer[i-1] == '\b') {
      /* remove this letter and if this is not the first key,
         remove the previous one as well */
      if(i > 1) {
        printf("\b \b");
        i = i - 2;
      }
      else {
        RingTheBell();
        i = i - 1;
      }
    }
    else if(buffer[i-1] != 13)
      putchar('*');

  } while((buffer[i-1] != 13) && (i < buflen));
  buffer[i-1] = '\0';
  printf("\r\n");
  return buffer;
}