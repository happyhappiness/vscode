from itertools import islice 
import srcml_api
import csv
import json
import my_constant
import my_util

def statistical_cluster(csv_file_name, statistic_file):
    """
    @ param csv file name and statistical file to write\n
    @ return statistical info about log records(number of instance, edit type frequence)\n
    @ involve get statistical info about cluster as well as all records\n
    """
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
        print >> statistic_file, "%s:%d," %(edit_type, edit_type_for_cluster_dict[edit_type]),
    print >> statistic_file, ''
    # show cluster result
    print >> statistic_file, "cluster is:%d, repeted cluster is:%d, repeted log is:%d" %(number_cluster, repeted_cluster, repeted_log)

    reading_file.close()

    return number_log, edit_type_for_log_dict

def statistical_rule_class(csv_file_name):
    """
    @ param csv file name\n
    @ return number of insert rule and number of modify rule\n
    @ involve count two sort of rules\n
    """
    reading_file = file(csv_file_name)
    records = csv.reader(reading_file)
    modify_counter = 0
    insert_counter = 0
    for record in islice(records, 1, None):
        old_loc = record[my_constant.CLASS_OLD_NEW_OLD_LOC]
        if old_loc == '-1':
            insert_counter += 1
        else:
            modify_counter += 1
    reading_file.close()
    return insert_counter, modify_counter


def statistical_repos_log(postfix=my_constant.LAST_REPOS, statistic_file_name = 'data/evaluate/statistics.txt'):
    """
    @ param postfix of csv file name, statistical file name\n
    @ return the line of logging codes\n
    @ involve sumarize logging LOC in given repos decided by postfix\n
    """
    statistic_file = open(statistic_file_name, 'ab')
    csv_file = file(my_util.concate_file(my_constant.ANALYZE_REPOS_LOG_FILE_NAME, postfix))
    records = csv.reader(csv_file)
    srcml = srcml_api.SrcmlApi()
    log_loc = 0
    counter = 0
    for record in islice(records, 1, None):
        counter += 1
        print 'now analyzing record: %d' %counter
        call_node_loc = int(record[my_constant.ANALYZE_REPOS_LOG_LOC])
        function_file = record[my_constant.ANALYZE_REPOS_LOG_FUNCTION]
        srcml.set_function_file(function_file)
        srcml.set_log_loc(call_node_loc)
        log_loc += len(srcml.get_log_loc(call_node_loc))
    print >> statistic_file, "\n# repos %s: %d" %(my_constant.REPOS, log_loc)
    csv_file.close()


def perform_statistic(statistic_file_name = 'data/evaluate/statistics.txt'):
    """
    @ param statistic file name\n
    @ return nothing\n
    @ involve get statistical info about cluster and log,
            edit type info and cluster info (no.cluster, no.>1cluster, no.repeted log)\n 
    """
    statistic_file = open(statistic_file_name, 'ab')
    print >> statistic_file, "\n#now analyzing repos:%s" %(my_constant.REPOS)
    # statistics about edition cluster
    print >> statistic_file, "#edition cluster info"
    edition_file_name = my_constant.CLUSTER_EDITION_OLD_NEW_FILE_NAME
    number_log, edit_type_for_log_dict = statistical_cluster(edition_file_name, statistic_file)
    print >> statistic_file, "#feature cluster info"
    # statistics about feature cluster
    feature_file_name = my_constant.CLUSTER_FEATURE_OLD_NEW_FILE_NAME
    statistical_cluster(feature_file_name, statistic_file)
    print >> statistic_file, "#edition and feature cluster info"
    # statistics about edition and feature cluster
    edition_and_feature_file_name = my_constant.CLUSTER_EDITION_AND_FEATURE_OLD_NEW_FILE_NAME
    statistical_cluster(edition_and_feature_file_name, statistic_file)
    print >> statistic_file, "#log info"
    print >> statistic_file, "number of log is:%d"  %number_log
    # show edition type result
    for edit_type in my_constant.LOD_EDIT_TYPES:
        print >> statistic_file, "%s:%d," %(edit_type, edit_type_for_log_dict[edit_type]),
    print >> statistic_file, ''
    # statistics about rule class
    insert_counter, modify_counter = statistical_rule_class(my_constant.CLASS_EDITION_AND_FEATURE_OLD_NEW_FILE_NAME)
    print >> statistic_file, '#rule info'
    print >> statistic_file, 'insert rule:%d, modify rule:%d' %(insert_counter, modify_counter)
    statistic_file.close()

"""
main function
"""
if __name__ == "__main__":
    perform_statistic()
