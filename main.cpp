/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: KnightDanila
 *
 * Created on 22 апреля 2019 г., 17:40
 */
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>

using namespace std;

/*
 * 
 */
template < typename T>
void println(T&& i) {
    cout << i << endl;
}

int main(int argc, char** argv) {

    FILE* file;
    file = fopen("test.txt", "rb+");
    if (file == NULL) {
        perror("Error opening file");
    } else {
        fseek(file, 0, SEEK_END);
        long int size = (unsigned long) ftell(file);
        printf("%ld\n", size);
        fseek(file, 0, SEEK_SET);

        char bytes[size];
        char origBytes [] = {0x0a, 0x00};
        //char newBytes [] = {0x11, 0x13};
        char newBytes [] = {0x0d, 0x0a};
        println(&bytes[0]);
        println(bytes[0]);
        println(newBytes[0]);
         
        if (fread(bytes, 1, size, file) != 0) {
            for (int i = 0; i < size; i++) {

                printf("%d\n", bytes[i]);
                printf("%d\n", &bytes[i]);
                printf("%d\n", origBytes);
                if (memcmp(&bytes[i], origBytes, 2) == 0) //Here the problem
                {
                    printf("Some: %c\n", bytes[i]);
                    fseek(file, i, SEEK_SET);
                    fwrite(newBytes, sizeof (char), 2, file);
                    //memcpy(destination, buffer, (size) * (count))
                    bytes[i] = newBytes[0];
                    bytes[i + 1] = newBytes[1];
                    //fseek(file, 0, SEEK_SET);
                }
            }
        }
        fclose(file);

    }
    system("pause");
    return 0;
}

