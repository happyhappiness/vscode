static struct curl_httppost *
AddHttpPost(char * name, long namelength,
            char * value, long contentslength,

            /* CMC: Added support for buffer uploads */
            char * buffer, long bufferlength,

            char *contenttype,
            long flags,
            struct curl_slist* contentHeader,
            char *showfilename,
            struct curl_httppost *parent_post,
            struct curl_httppost **httppost,
            struct curl_httppost **last_post)
{
  struct curl_httppost *post;
  post = (struct curl_httppost *)malloc(sizeof(struct curl_httppost));
  if(post) {
    memset(post, 0, sizeof(struct curl_httppost));
    post->name = name;
    post->namelength = name?(namelength?namelength:(long)strlen(name)):0;
    post->contents = value;
    post->contentslength = contentslength;

    /* CMC: Added support for buffer uploads */
    post->buffer = buffer;
    post->bufferlength = bufferlength;

    post->contenttype = contenttype;
    post->contentheader = contentHeader;
    post->showfilename = showfilename;
    post->flags = flags;
  }
  else
    return NULL;
  
  if (parent_post) {
    /* now, point our 'more' to the original 'more' */
    post->more = parent_post->more;
    
    /* then move the original 'more' to point to ourselves */
    parent_post->more = post;	         
  }
  else {
    /* make the previous point to this */
    if(*last_post)
      (*last_post)->next = post;
    else
      (*httppost) = post;
    
    (*last_post) = post;  
  }
  return post;
}