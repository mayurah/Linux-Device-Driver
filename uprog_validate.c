#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
char estring[256] = "HPE HACKATHON 2016!!";

int main()
{
	int fd;
	char *addr;

	fd = open("/dev/hpehackon", O_RDWR);
	if (fd == -1) {
		fprintf(stderr, "failed to open the device file /dev/hpehackon\n");
		exit (1);
	}

	addr = (char *)mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	if (addr != MAP_FAILED) {
		fprintf(stderr, "mmap should not succeed with write permission\n");
		exit (1);
	}

	addr = (char *)mmap(NULL, 4096, PROT_READ, MAP_SHARED, fd, 0);

	if (addr == MAP_FAILED) {
		fprintf(stderr, "failed to mmap from the device file\n");
		exit (1);
	}

	if (strncmp(addr, estring, 256) != 0) {
		fprintf(stderr, "failed to find the expected string in mmaped memory\n");
		exit (1);
	}
	printf("%s\n", addr);

	if (munmap(addr, 4096) != 0) {
		fprintf(stderr, "failed to unmap the mmaped memory\n");
		exit (1);
	}
	close(fd);
	printf("Success\n");
	exit(0);
}
