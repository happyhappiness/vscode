r(i=0;i<=New_Field->nbuf;i++)
		{
		  New_Field->buf[(New_Field->drows*New_Field->cols+1)*(i+1)-1]
		    = '\0';
		}