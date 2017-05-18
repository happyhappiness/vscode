#-*-coding: utf-8 -*-
import similarity_func
import cluster_control
import analyze_control
import csv
"""
@ param  var to deal with
@ return list of analyzed node info
@ callee ...
@ caller analyze_control.py, similarity_func.py ..
@ involve remove namespace bafore ::, and remove caller before ->, .
"""
def removeNamespace(name):
    # remove namespace before ::
    startpos = name.find("::")
    while startpos != -1:
        name = name[startpos + 2:]
        startpos = name.find("::")

    # remove caller before ->
    startpos = name.find("->")
    while startpos != -1:
        name = name[startpos + 2:]
        startpos = name.find("->")
    name = name.strip()

    # remove caller before ->
    startpos = name.find(".")
    while startpos != -1:
        name = name[startpos + 2:]
        startpos = name.find(".")
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

"""
@ param  filename
@ return function_similarity_dic
@ callee similarity_func.getFunctionSimilarity
@ caller cluster_context_with_function
@ involve call similarity_func.getFunctionSimilarity to get similarity_dic between functions
"""
def getFunctionSimilarityDic(isFromRead,fileName):

    func_similarity_dic = {}
    if isFromRead:
        # initialize func_similarity_dict
        analyze_func = file(fileName, 'rb')
        func_records = csv.reader(analyze_func)
        for func_record in func_records:
            func_similarity_dic[(func_record[0], func_record[1])] = func_record[2]
        analyze_func.close()
    else:
        func_similarity_dic = similarity_func.getFunctionSimilarity(fileName)
    return func_similarity_dic

"""
@ param  log id and joern instance
@ return cdg_list, neighbor_list, context_list, ddg_list, static_list
@ callee analyze_control.getContextOfLog
@ caller cluster_context_with_function
@ involve get context infomation of given log id
"""
def getContextInfo(log_id, joern_instance):

    cdg_list, neighbor_list, context_list, ddg_node,\
         ddg_list, static_list = analyze_control.getContextOfLog(str(log_id), joern_instance)
    return cdg_list, neighbor_list, context_list, ddg_list, static_list

"""
@ param  similarity_dic, filename
@ return ...
@ callee ...
@ caller self, cluster_context_with_function
@ involve dump similarity_dic into given fileName
"""
def dumpSimilarityDic(similarity_dic, fileName):

    similarity_control = file(fileName, 'wb')
    similarity_control_writer = csv.writer(similarity_control)
    similarity_control_writer.writerow(["left", "right", "similarity"])
    # dump similarity
    for pair, similarity in similarity_dic.items():
        if pair[0] >= 0 and pair[1] >= 0:
            similarity_control_writer.writerow([pair[0], pair[1], similarity])

    # close files
    similarity_control.close()

"""
@ param  context_lists, func_similarity_dic, cluster_similarity
@ return cluster_lists
@ callee cluster_control.cluster_record
@ caller cluster_context_with_function
@ involve cluster the context_lists according to cluster_similarity
"""
def performCluster(context_lists, func_similarity_dic, cluster_similarity, fileName):

    cluster_lists, similarity_dic = cluster_control.cluster_record(context_lists, func_similarity_dic, cluster_similarity)
    dumpSimilarityDic(similarity_dic, fileName)

    return cluster_lists


"""
@ param  dict, key_index
@ return dict
@ callee ...
@ caller cluster_control.computeSim
@ involve remove key contains key_a or key_b specified key_index
"""
def removeDicElement(dictionary, key_index):

    key_list = dictionary.keys()
    key_a = key_list[key_index][0]
    key_b = key_list[key_index][1]
    for key in key_list:
        # if key contains key_a or key_b
        if key[0] == key_a or key[1] == key_b:
            del dictionary[key]

    return dictionary

list_a = [[["chroot", "char [ MAX_STRING_LENGTH + 1 ]"]], [["!", "strcasecmp", "config_getoption", "\"DO_CHROOT\"", "\"yes\""]], [["!", "char *", "0"]], [["int"]], [["!", "char *", "0"]], [["!", "int"]]]
list_b = [[["chroot", "char *"]], [["!", "strcasecmp", "config_getoption", "\"DO_CHROOT\"", "\"yes\""]], [["!", "char *", "0"]], [["int"]], [["!", "char *", "0"]], [["!", "int"]]]
cluster_control.computeSim(list_a, list_b, {})