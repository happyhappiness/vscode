int main(int argc, char **argv)
{
  if(argc< 3) {
    printf("./moo main sub\n");
  }
  else {
    int size;
    char *buffer = spitout(stdin, argv[1], argv[2], &size);
  }
  return 0;
}