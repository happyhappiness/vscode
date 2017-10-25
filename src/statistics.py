from itertools import islice 
import csv
import json
import my_constant

"""
@ param csv file name
@ return statistic info(no.cluster, no.>1cluster, no.repeted log) 
@ involve get statistical info about cluster
"""
def statistical_cluster(csv_file_name):
    reading_file = file(csv_file_name)
    records = csv.reader(reading_file)
    # define and initialize edit type dictary type -> number of instances
    edit_type_for_log_dict = {}
    edit_type_for_cluster_dict = {}
    for i in my_constant.LOD_EDIT_TYPES:
        edit_type_for_log_dict[i] = 0
        edit_type_for_cluster_dict[i] = 0
    # define and initialize log edit dict
    log_edit_dict = {}
    # cluster dictary: cluster index -> cluster size
    cluster_dict = {}
    number_log = 0
    number_cluster = 0
    repeted_cluster = 0
    repeted_log = 0
    for record in islice(records, 1, None):
        number_log += 1
        # record number of instance for each edit type
        edit_types = json.loads(record[my_constant.ANALYZE_EDIT_TYPE])
        for edit_type in edit_types:
            edit_type_for_log_dict[edit_type] += 1
        # filter by edit feature != 0 (cluster of empty edit is unsure)
        edit_feature = json.loads(record[my_constant.ANALYZE_EDIT_FEATURE])
        if edit_feature == [0]:
            continue
        cluster = json.loads(record[my_constant.ANALYZE_CLUSTER])
        # record number of cluster for each cluster index
        # if has been in dict -> repeted log and cluster size
        if cluster_dict.has_key(cluster):
            # current edit type info
            for edit_type in edit_types:
                edit_type_for_cluster_dict[edit_type] += 1
            # first repetetion -> repeted cluster and repeted log(historical one)
            if len(cluster_dict[cluster]) == 1:
                # historical edit type info
                edit_types = log_edit_dict[cluster_dict[cluster][0]]
                for edit_type in edit_types:
                    edit_type_for_cluster_dict[edit_type] += 1
                repeted_cluster += 1
                repeted_log += 1
            # if have repetion, increment value(mark)
            cluster_dict[cluster].append(number_log)
            # repeted log
            repeted_log += 1
        # new cluster -> cluster count and cluster size
        else:
            # record log edit info for each log
            log_edit_dict[number_log] = edit_types
            cluster_dict[cluster] = [number_log]
            number_cluster += 1

    # show edition type result
    for edit_type in my_constant.LOD_EDIT_TYPES:
        print "%s: %d" %(edit_type, edit_type_for_cluster_dict[edit_type]),
    print ''
    # show cluster result
    print "cluster is %d, repeted cluster is %d, repeted log is %d" %(number_cluster, repeted_cluster, repeted_log)

    reading_file.close()

    return number_log, edit_type_for_log_dict

"""
@ param none(my_constant.repos name)
@ return statistic info(edition type info and no.cluster, no.>1cluster, no.repeted log) 
@ involve get statistical info about cluster
"""
def perform_statistic():

    # statistics about edition cluster
    print "----------------------edition cluster info-------------------"
    edition_file_name = my_constant.CLUSTER_EDITION_OLD_NEW_FILE_NAME
    number_log, edit_type_for_log_dict = statistical_cluster(edition_file_name)
    print "----------------------edition and feature cluster info-------------------"
    # statistics about edition and feature cluster
    edition_and_feature_file_name = my_constant.CLUSTER_EDITION_AND_FEATURE_OLD_NEW_FILE_NAME
    statistical_cluster(edition_and_feature_file_name)
    print "----------------------log info-------------------"
    print "number of log is %d "  %number_log
    # show edition type result
    for edit_type in my_constant.LOD_EDIT_TYPES:
        print "%s: %d" %(edit_type, edit_type_for_log_dict[edit_type]),
    print ''

if __name__ == "__main__":
    perform_statistic()
