import urllib2
import re
import my_constant

"""
@ param main url and file name
@ return
@ involve download tar.gz from given url
"""
def download_file(main_url, file_name):
    file_url = main_url + file_name
    file_content = urllib2.urlopen(file_url)

    download_tar_file = open(file_name, 'wb')
    block_size = 8192
    while True:
        cache = file_content.read(block_size)
        if not cache:
            break
        download_tar_file.write(cache)
    download_tar_file.close()

    return True

"""
@ param url
@ return
@ involve deal with each href and download tar.gz
"""
def analyze_html(url):
    # fetch html
    response = urllib2.urlopen(url)
    html = response.read().split("\n")
    target_href_pattern = r'(?:href|HREF)="(git-2\..*\.tar\.gz)"'
    count = 0
    # check html content against git-2.*.tar.gz
    for line in html:
        is_target = re.search(target_href_pattern, line, re.I)
        if is_target:
            file_name = is_target.group(1)
            if download_file(url, file_name):
                count += 1
                print "now downloading %d:%s" %(count, file_name)

"""
main function
"""
if __name__ == "__main__":
    analyze_html("https://www.kernel.org/pub/software/scm/git/")