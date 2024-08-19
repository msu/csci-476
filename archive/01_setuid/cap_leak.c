#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void main()
{
    int fd;

    /*
     * Assume that /etc/zzz is an important system file,
     * and it is owned by root with permission 0644.
     * Before running this program, you should create
     * the file /etc/zzz first.
     */
    fd = open("/etc/zzz", O_RDWR | O_APPEND);
    if (fd == -1) {
        printf("Cannot open /etc/zzz\n");
        exit(0);
    }

    // Simulate the tasks conducted by the program
    sleep(1);

    /*
     * After the task, elevated privileges are no longer needed;
     * it is time to relinquish these privileges!
     * NOTE: getuid() returns the real UID (RUID)
     */
    setuid(getuid());

    if (fork()) {  /* parent process */
        close (fd);
        exit(0);
    } else {  /* child process */

        /*
         * Now, assume that the child process is compromised, and that
         * malicious attackers have injected the following statements into this process
         */
        write (fd, "Malicious Data\n", 15);
        close (fd);
    }
}
