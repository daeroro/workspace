#include "can_serial.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>

extern char can_tx_buf[22];
extern char *dev0;
int emergency_fd;

void emergency(int signo);
void vcp_can_tx(int fd);

int main(void)
{
	char buf[32] = "text message\r\n";
	int len = strlen(buf);
	int fd;

	fd = serial_config(dev0);

	vcp_can_tx(fd);

	send_data(fd, buf, len, 50);
	recv_data(fd);

	close_dev(fd);	

	return 0;
}

void emergency(int signo)
{
	char stop[32] = {0, '1', '5', '0', '0'};
	set_bldc_tx_buf(stop, can_tx_buf, 'd');
	write(emergency_fd, can_tx_buf, 21);
	printf("BLDC Stop\n");

	close_dev(emergency_fd);

	sleep(3);
	exit(0);	
}

void vcp_can_tx(int fd)
{
	int usb2can = fd;

	char start[32] = {0, '1', '5', '6', '0'};
	char min[32] = {0, '0', '0', '0', '0'};
	char max[32] = {0, '3', '0', '0', '0'};

	signal(SIGINT, emergency);
	emergency_fd = usb2can;

	for(;;)
	{
		printf("If DSP get the Lane then start - sleep(1)\n");

	}
}
