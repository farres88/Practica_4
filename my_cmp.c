#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Error faltan nombres de archivos\n");
        return -1;
    }


    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) {
        perror("Error al abrir archivo 1");
        return -1;
    }


    int fd2 = open(argv[2], O_RDONLY);
    if (fd2 == -1) {
        perror("Error al abrir archivo 2");
        close(fd1);
        return -1;
    }


    char buf1[1], buf2[1];
    int byte_pos = 1, line_num = 1;
    ssize_t read1, read2;


    while ((read1 = read(fd1, buf1, 1)) > 0 && (read2 = read(fd2, buf2, 1)) > 0) {
        if (buf1[0] != buf2[0]) {
            printf("Diferente el byte %d, linea %d\n", byte_pos, line_num);
            close(fd1);
            close(fd2);
            return 0;
        }
        if (buf1[0] == '\n') {
            line_num++;
        }
        byte_pos++;
    }


    if (read1 > 0 || read2 > 0) {
        printf("uno de los archivos es mas largo\n");
    }


    close(fd1);
    close(fd2);
    return 0;
}

