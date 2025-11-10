#include "../include/utils.h" // Meng-include file "UUD" kita

int main(int argc, char *argv[])
{
    int status;

    if (argc != 3)
    {
        printf("Input tidak valid.\n");
        printf("Cara pakai: ./aplikasijadi <username> <password>\n");
        return 1;
    }

    // Panggil fungsi login yang sudah ada
    status = login(argv[1], argv[2]);

    if (status == 1)
    {
        printf("Welcome admin.\n");
        menu_admin(); // Panggil menu admin
    }
    else if (status == 2)
    {
        printf("Welcome user.\n");
        menu_user(); // Panggil menu user
    }
    else
    {
    }

    printf("Program Selesai.\n");
    return 0;
}