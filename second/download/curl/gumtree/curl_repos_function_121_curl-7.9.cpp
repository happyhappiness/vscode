static struct HttpPost * AddHttpPost (char * name,
                                      long namelength,
                                      char * value,
                                      long contentslength,
				      char *contenttype,
                                      long flags,
                                      struct HttpPost *parent_post,
                                      struct HttpPost **httppost,
                                      struct HttpPost **last_post)
{
  struct HttpPost *post;
  post = (struct HttpPost *)malloc(sizeof(struct HttpPost));
  if(post) {
    memset(post, 0, sizeof(struct HttpPost));
    post->name = name;
    post->namelength = namelength;
    post->contents = value;
    post->contentslength = contentslength;
    post->contenttype = contenttype;
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