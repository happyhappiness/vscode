    s[j++]="end\n";
    s[j++]="mt.__index = function (t, n)\n";
    s[j++]="  if dbg.getinfo(2) and dbg.getinfo(2, \"S\").what ~= \"C\" then\n";
    s[j++]="    error(\"Script attempted to access nonexistent global variable '\"..tostring(n)..\"'\", 2)\n";
    s[j++]="  end\n";
    s[j++]="  return rawget(t, n)\n";
    s[j++]="end\n";
