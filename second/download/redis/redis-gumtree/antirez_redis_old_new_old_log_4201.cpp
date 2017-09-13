lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",
		 withscores ? (rangelen*2) : rangelen);