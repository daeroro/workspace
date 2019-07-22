#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	int i=0;
	int len;
	int rfd, wfd;
	int nr;
	
	char buf[64] = {0};
//	char text[64] = "Hello Linux System Programming!\n";

	rfd = open("reading.txt", O_RDONLY, 0644);
	wfd = open("test.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);

	printf("rfd = %d, wfd = %d\n", rfd, wfd);

	while((nr = read(rfd, buf, sizeof(buf)))>0)
		write(wfd, buf, nr);

	close(rfd);
	close(wfd);
	return 0;
}
