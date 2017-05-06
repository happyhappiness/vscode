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


"""
@ param  element and in_list
@ return in_list
@ callee ...
@ caller cluster_control
@ involve remove given element in in_list
"""
def removeGivenElement(element, in_list):
    # remove element in in_list
    while element in in_list:
        in_list.remove(element)

    return in_list
