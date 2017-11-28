void
ConfigParser::destruct()
{
    shutting_down = 1;
    if (!CfgFiles.empty()) {
        std::ostringstream message;
        CfgFile *f = CfgFiles.top();
        message << "Bungled " << f->filePath << " line " << f->lineNo <<
                ": " << f->currentLine << std::endl;
        CfgFiles.pop();
        delete f;
        while (!CfgFiles.empty()) {
            f = CfgFiles.top();
            message << " included from " << f->filePath << " line " <<
                    f->lineNo << ": " << f->currentLine << std::endl;
            CfgFiles.pop();
            delete f;
        }
        message << " included from " <<  cfg_filename << " line " <<
                config_lineno << ": " << config_input_line << std::endl;
        std::string msg = message.str();
        fatalf("%s", msg.c_str());
    } else
        fatalf("Bungled %s line %d: %s",
               cfg_filename, config_lineno, config_input_line);
}