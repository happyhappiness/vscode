#-*-coding: utf-8 -*-

"""
@ param  var to deal with
@ return list of analyzed node info
@ callee ...
@ caller analyze_control.py, similarity_func.py ..
@ involve remove namespace bafore ::
"""
def removeNamespace(name):
    startpos = name.find("::")
    while startpos != -1:
        name = name[startpos + 2:]
        startpos = name.find("::")
    name = name.strip()

    return name
    