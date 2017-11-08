static
int FormParse(char *input,
	      struct curl_httppost **httppost,
	      struct curl_httppost **last_post)
{
  /* nextarg MUST be a string in the format 'name=contents' and we'll
     build a linked list with the info */
  char name[256];
  char *contents;
  char major[128];
  char minor[128];
  long flags = 0;
  char *contp;
  const char *type = NULL;
  char *prevtype = NULL;
  char *sep;
  char *sep2;
  struct curl_httppost *post;
  struct curl_httppost *subpost; /* a sub-node */
  unsigned int i;

  /* Preallocate contents to the length of input to make sure we don't
     overwrite anything. */
  contents = malloc(strlen(input));
  contents[0] = '\000';
 
  if(1 <= sscanf(input, "%255[^=]=%[^\n]", name, contents)) {
    /* the input was using the correct format */
    contp = contents;

    if('@' == contp[0]) {
      /* we use the @-letter to indicate file name(s) */
      
      flags = HTTPPOST_FILENAME;
      contp++;

      post=NULL;

      do {
	/* since this was a file, it may have a content-type specifier
	   at the end too */

	sep=strchr(contp, FORM_TYPE_SEPARATOR);
	sep2=strchr(contp, FORM_FILE_SEPARATOR);

	/* pick the closest */
	if(sep2 && (sep2 < sep)) {
	  sep = sep2;

	  /* no type was specified! */
	}
	if(sep) {

	  /* if we got here on a comma, don't do much */
	  if(FORM_FILE_SEPARATOR != *sep)
	    type = strstr(sep+1, "type=");
	  else
	    type=NULL;

	  *sep=0; /* terminate file name at separator */

	  if(type) {
	    type += strlen("type=");
	    
	    if(2 != sscanf(type, "%127[^/]/%127[^,\n]",
			   major, minor)) {
              free(contents);
	      return 2; /* illegal content-type syntax! */
	    }
	    /* now point beyond the content-type specifier */
	    sep = (char *)type + strlen(major)+strlen(minor)+1;

	    /* find the following comma */
	    sep=strchr(sep, FORM_FILE_SEPARATOR);
	  }
	}
	else {
	  type=NULL;
	  sep=strchr(contp, FORM_FILE_SEPARATOR);
	}
	if(sep) {
	  /* the next file name starts here */
	  *sep =0;
	  sep++;
	}
	if(!type) {
	  /*
	   * No type was specified, we scan through a few well-known
	   * extensions and pick the first we match!
	   */
	  struct ContentType {
	    const char *extension;
	    const char *type;
	  };
          static struct ContentType ctts[]={
	    {".gif",  "image/gif"},
	    {".jpg",  "image/jpeg"},
	    {".jpeg", "image/jpeg"},
	    {".txt",  "text/plain"},
	    {".html", "text/plain"}
	  };

	  if(prevtype)
	    /* default to the previously set/used! */
	    type = prevtype;
	  else
	    /* It seems RFC1867 defines no Content-Type to default to
	       text/plain so we don't actually need to set this: */
	    type = HTTPPOST_CONTENTTYPE_DEFAULT;

	  for(i=0; i<sizeof(ctts)/sizeof(ctts[0]); i++) {
	    if(strlen(contp) >= strlen(ctts[i].extension)) {
	      if(strequal(contp +
			  strlen(contp) - strlen(ctts[i].extension),
			  ctts[i].extension)) {
		type = ctts[i].type;
		break;
	      }	      
	    }
	  }
	  /* we have a type by now */
	}

	if(NULL == post) {
	  /* For the first file name, we allocate and initiate the main list
	     node */

	  post = (struct curl_httppost *)malloc(sizeof(struct curl_httppost));
	  if(post) {
	    memset(post, 0, sizeof(struct curl_httppost));
	    GetStr(&post->name, name);      /* get the name */
	    GetStr(&post->contents, contp); /* get the contents */
            post->contentslength = 0;
	    post->flags = flags;
	    if(type) {
	      GetStr(&post->contenttype, (char *)type); /* get type */
	      prevtype=post->contenttype; /* point to the allocated string! */
	    }
	    /* make the previous point to this */
	    if(*last_post)
	      (*last_post)->next = post;
	    else
	      (*httppost) = post;

	    (*last_post) = post;	  
	  }

	}
	else {
	  /* we add a file name to the previously allocated node, known as
             'post' now */
	  subpost =(struct curl_httppost *)
            malloc(sizeof(struct curl_httppost));
	  if(subpost) {
	     memset(subpost, 0, sizeof(struct curl_httppost));
	     GetStr(&subpost->name, name);      /* get the name */
	     GetStr(&subpost->contents, contp); /* get the contents */
             subpost->contentslength = 0;
	     subpost->flags = flags;
	     if(type) {
	       GetStr(&subpost->contenttype, (char *)type); /* get type */
	       prevtype=subpost->contenttype; /* point to allocated string! */
	     }
	     /* now, point our 'more' to the original 'more' */
	     subpost->more = post->more;

	     /* then move the original 'more' to point to ourselves */
	     post->more = subpost;	     
	  }
	}
	contp = sep; /* move the contents pointer to after the separator */
      } while(sep && *sep); /* loop if there's another file name */
    }
    else {
      post = (struct curl_httppost *)malloc(sizeof(struct curl_httppost));
      if(post) {
	memset(post, 0, sizeof(struct curl_httppost));
	GetStr(&post->name, name);      /* get the name */
	if( contp[0]=='<' ) {
	  GetStr(&post->contents, contp+1); /* get the contents */
          post->contentslength = 0;
	  post->flags = HTTPPOST_READFILE;
	}
	else {
	  GetStr(&post->contents, contp); /* get the contents */
          post->contentslength = 0;
	  post->flags = 0;
	}

	/* make the previous point to this */
	if(*last_post)
	  (*last_post)->next = post;
	else
	  (*httppost) = post;

	(*last_post) = post;	  
      }

    }

  }
  else {
    free(contents);
    return 1;
  }
  free(contents);
  return 0;
}