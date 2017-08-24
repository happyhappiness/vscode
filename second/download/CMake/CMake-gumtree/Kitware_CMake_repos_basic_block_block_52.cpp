{
      FIELD *f;

      for(f=field;f->link != field;f = f->link) 
	{}
      f->link = field->link;
    }