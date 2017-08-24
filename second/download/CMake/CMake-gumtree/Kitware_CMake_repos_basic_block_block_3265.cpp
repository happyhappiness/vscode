{
        if (ISFLAG("--")) { decode = False; continue; }
            if (aa->name[0] == '-' && decode) continue;
            numFilesProcessed++;
            testf ( aa->name );
     }