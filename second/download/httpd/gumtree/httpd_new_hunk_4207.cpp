	}
    }
    if (!found) {
	printf("Adding user %s\n", user);
	add_password(user, tfp);
    }
/*
* make a copy from the tmp file to the actual file
*/  
        rewind(f);
        rewind(tfp);
        while ( fgets(command,MAX_STRING_LEN,tfp) != NULL)
        {
                fputs(command,f);
        } 

    fclose(f);
    fclose(tfp);
    unlink(tn);
    exit(0);
}
