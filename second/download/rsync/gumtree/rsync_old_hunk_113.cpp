   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "rsync.h"

extern int csum_length;

/*
  a simple 32 bit checksum that can be upadted from either end
  (inspired by Mark Adler's Adler-32 checksum)
  */
uint32 get_checksum1(char *buf,int len)
{
    int i;
    uint32 s1, s2;

    s1 = s2 = 0;
    for (i = 0; i < len; i++) {
	s1 += buf[i];
	s2 += s1;
    }
    return (s1 & 0xffff) + (s2 << 16);
}


void get_checksum2(char *buf,int len,char *sum)
{
  char buf2[64];
  int i;
  MDstruct MD;

  MDbegin(&MD);
  for(i = 0; i + 64 <= len; i += 64) {
    bcopy(buf+i,buf2,64);
    MDupdate(&MD, buf2, 512);
  }
  bcopy(buf+i,buf2,len-i);
  MDupdate(&MD, buf2, (len-i)*8);
  SIVAL(sum,0,MD.buffer[0]);
  if (csum_length <= 4) return;
  SIVAL(sum,4,MD.buffer[1]);
  if (csum_length <= 8) return;
  SIVAL(sum,8,MD.buffer[2]);
  if (csum_length <= 12) return;
  SIVAL(sum,12,MD.buffer[3]);
}

void file_checksum(char *fname,char *sum,off_t size)
{
  char *buf;
  int fd;
  bzero(sum,csum_length);

  fd = open(fname,O_RDONLY);
  if (fd == -1) return;

  buf = map_file(fd,size);
  if (!buf) {
    close(fd);
    return;
  }

  get_checksum2(buf,size,sum);
  close(fd);
  unmap_file(buf,size);
}
