
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(void) {
    const char *msg = "hello, kernel\n";

    // Open the file for writing
    int fd = open("note.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd < 0) {
        perror("open");
        return 1;
    }

    printf("open returned descriptor %d\n", fd);

    // Write the message into the file
    ssize_t n = write(fd, msg, strlen(msg));

    if (n != (ssize_t)strlen(msg)) {
        perror("write");
        close(fd);
        return 1;
    }

    printf("write sent %zd bytes\n", n);
    close(fd);

    // Open the file again for reading
    fd = open("note.txt", O_RDONLY);

    if (fd < 0) {
        perror("open");
        return 1;
    }

    char buf[64];

    // Read the data from the file
    n = read(fd, buf, sizeof(buf) - 1);

    if (n < 0) {
        perror("read");
        close(fd);
        return 1;
    }

    buf[n] = '\0';

    printf("read got %zd bytes: %s", n, buf);

    close(fd);

    return 0;
}

