#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return -1;
    }

    char *nom_arxiu = argv[1];

    //Crear archivo
    int fd = open(nom_arxiu, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        return -1;
    }

    ssize_t leido;
    char buf[1];

    //Leer todo carac uno a uno, escribir en archivo y salida
    while ((leido = read(STDIN_FILENO, buf, 1)) > 0) {
        if (write(fd, buf, leido) == -1) {
            perror("Error al escribir en archivo");
            close(fd);
            return -1;
        }
        if (write(STDOUT_FILENO, buf, leido) == -1) { //STDOUT_FILENO = standard input imrpime en pantalla
            perror("Error al escribir en pantalla");
            close(fd);
            return -1;
        }
    }

    if (leido == -1) {
        perror("Error al leer");
    }

    //Cerrar archivo
    if (close(fd) == -1) {
        perror("Error al cerrar el archivo");
        return -1;
    }

    return 0;
}

