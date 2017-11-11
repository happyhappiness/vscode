int main(int argc, char **argv) {
  int c;
  if (argc < 3) usage(argv[0]);
  
  machine = argv[1]; 
  file = argv[2];
  optind = 3;
  while ((c = getopt(argc,argv,"p:n:c:d:t:d:k"))>0) {
    switch(c) {
    case 'd':
      break;
    case 'n': 
      requests = atoi(optarg);
      if(!requests) {
	printf("Invalid number of requests\n");
	exit(1);
      }
      break;
    case 'k':
      keepalive=1;
      break;
    case 'c':
      concurrency = atoi(optarg);
      break;
    case 'p':
      port = atoi(optarg);
      break;
    case 't':
      tlimit = atoi(optarg);
      requests = MAX_REQUESTS;  /* need to size data array on something */
      break;
    default:
      usage(argv[0]);
      break;
    }
  }   
  test();
  return 0;
}