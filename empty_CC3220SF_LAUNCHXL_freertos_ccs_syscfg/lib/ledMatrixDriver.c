/*
 * ledMatrixDriver.c
 *
 *  Created on: 27. 4. 2019
 *      Author: lukelee36
 */

#include "ledMatrixDriver.h"
#include <ti/drivers/GPIO.h>
#include "Board.h"
#include <stdio.h>
#include <string.h>

static unsigned int ptr1[16][32] =
{
     {OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED},
     {OFFLED,OFFLED,ONLED,ONLED,OFFLED,OFFLED,ONLED,ONLED,OFFLED,OFFLED,OFFLED,ONLED,OFFLED,OFFLED,OFFLED,OFFLED,ONLED,OFFLED,ONLED,ONLED,ONLED,OFFLED,ONLED,OFFLED,OFFLED,ONLED,ONLED,ONLED,ONLED,ONLED,OFFLED,OFFLED},
     {OFFLED,OFFLED,ONLED,OFFLED,ONLED,OFFLED,ONLED,OFFLED,ONLED,OFFLED,ONLED,OFFLED,ONLED,OFFLED,OFFLED,OFFLED,ONLED,OFFLED,ONLED,OFFLED,OFFLED,OFFLED,ONLED,OFFLED,ONLED,OFFLED,OFFLED,ONLED,OFFLED,OFFLED,OFFLED,OFFLED},
     {OFFLED,OFFLED,ONLED,ONLED,OFFLED,OFFLED,ONLED,ONLED,OFFLED,OFFLED,ONLED,OFFLED,ONLED,OFFLED,OFFLED,OFFLED,ONLED,OFFLED,ONLED,ONLED,OFFLED,OFFLED,ONLED,ONLED,OFFLED,OFFLED,OFFLED,ONLED,OFFLED,OFFLED,OFFLED,OFFLED},
     {OFFLED,OFFLED,ONLED,OFFLED,OFFLED,OFFLED,ONLED,OFFLED,ONLED,OFFLED,ONLED,OFFLED,ONLED,OFFLED,ONLED,OFFLED,ONLED,OFFLED,ONLED,OFFLED,OFFLED,OFFLED,ONLED,OFFLED,ONLED,OFFLED,OFFLED,ONLED,OFFLED,OFFLED,OFFLED,OFFLED},
     {OFFLED,OFFLED,ONLED,OFFLED,OFFLED,OFFLED,ONLED,OFFLED,ONLED,OFFLED,OFFLED,ONLED,OFFLED,OFFLED,OFFLED,ONLED,OFFLED,OFFLED,ONLED,ONLED,ONLED,OFFLED,ONLED,OFFLED,ONLED,OFFLED,OFFLED,ONLED,OFFLED,OFFLED,OFFLED,OFFLED},
     {OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED},
     {OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED},
     {OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,ONLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,ONLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED},
     {OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,ONLED,ONLED,ONLED,OFFLED,OFFLED,OFFLED,ONLED,ONLED,ONLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED},
     {OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,ONLED,OFFLED,OFFLED,ONLED,OFFLED,OFFLED,ONLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED},
     {OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,ONLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED},
     {OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,ONLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,ONLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED},
     {OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,ONLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,ONLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED},
     {OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,ONLED,ONLED,ONLED,ONLED,ONLED,ONLED,ONLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED},
     {OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED,OFFLED}

};

static unsigned int rows1[8][32] = { 0 };
static unsigned int rows2[8][32] = { 0 };
//memset(row1, 0, sizeof(row1));
//memset(row2, 0, sizeof(row2));

void lmd_show_char(uint8_t position, int rows, int character)
{
    int i,j;
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 5; ++j)
        {
            if(rows == ROWS1)
            {
                memcpy(&rows1[i][j+1+(position*5)], &Malphabet[i][j+(character*5)], sizeof(unsigned int));
            }

            if(rows == ROWS2)
            {
                memcpy(&rows2[i][j+1+(position*5)], &Malphabet[i][j+(character*5)], sizeof(unsigned int));
            }
        }
    }
}


void lmd_show_char_a(uint8_t position, int rows)
{
    int i,j;
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 5; ++j)
        {
            if(rows == ROWS1)
            {
                memcpy(&rows1[i][j+1+(position*5)], &Malphabet[i][j], sizeof(unsigned int));
            }

            if(rows == ROWS2)
            {
                memcpy(&rows2[i][j+1+(position*5)], &Malphabet[i][j], sizeof(unsigned int));
            }
        }
    }
}

void loadMatrixData(uint8_t addr)
{
    int j;

    //lmd_demo_alphabeth();

    lmd_show_text("AhojkyMam to");

    for(j = 0; j < 32; j++)
    {
        lmd_write_pixel(R1Matrix, rows1[addr][j]);
        lmd_write_pixel(R2Matrix, rows2[addr][j]);
        //GPIO_write(R1Matrix, row1[addr][j]);
        //GPIO_write(R2Matrix, row2[addr][j]);
//      GPIO_write(R2Matrix, ptr[j]);
        GPIO_write(CLKMatrix, tick);
       // usleep(100);

        GPIO_write(CLKMatrix, toc);
    }
}

void lmd_write_pixel(int pinRow, unsigned int data)
{
    if(data)
    {
        GPIO_write(pinRow, ONLED);
    }
    else
    {
        GPIO_write(pinRow, OFFLED);
    }
}

void lmd_demo_alphabeth(void)
{
    static int counter = 0;

    if(counter < 500)
    {
        lmd_demo_alphabeth_list(0);
    }
    else if(counter < 1000)
    {
        lmd_demo_alphabeth_list(1);
    }
    else
    {
        lmd_demo_alphabeth_list(2);

    }
    counter++;

    if(counter == 3000)
    {
        counter = 0;
    }
}


void lmd_demo_alphabeth_list(int list)
{
    int i = list;
    int j = 0;

    for(j; j<12; j++)
    {
        if(j<6)
        {
            lmd_show_char(j, ROWS1, j+(i*12));
        }
        else
        {
            lmd_show_char(j-6, ROWS2, j+(i*12));
        }
    }
}

void lmd_show_text(char text[])
{
    // this is part where I want to parse text to character
    int max = strlen(text);
    int i;

    for (i = 0; i < max; ++i)
    {
        if(i<6)
        {
            lmd_find_char(text[i], ROWS1, i);
        }
        else
        {
            lmd_find_char(text[i], ROWS2, i-6);
        }
    }

}

void lmd_find_char(char character, int rows, int position )
{
    // this is the part where I count number from ascii to my alphabeth with 36 char since number 0-9
   // int ch = atoi(character);
    // A == 65, Z == 90, 0 == 48, 9 == 57
    if(character>='a' && character<='z')
    {
        character = toupper(character);
    }

    if(character>='A' && character<='Z')
    {
        lmd_show_char(position, rows, character-65);
    }
    else if(character>='0' && character<='9')
    {
        lmd_show_char(position, rows, character-22);
    }
    else
    {
        lmd_show_char(position, rows, 36);
    }
}

